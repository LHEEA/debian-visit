/*****************************************************************************
*
* Copyright (c) 2000 - 2017, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//  File: avtThreeSliceFilter.C
// ************************************************************************* //

#include <avtThreeSliceFilter.h>

#include <vtkDataSet.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyData.h>
#include <vtkRectilinearGrid.h>
#include <vtkSlicer.h>
#include <vtkExecutive.h>

#include <DebugStream.h>

// ****************************************************************************
//  Method: avtThreeSliceFilter constructor
//
//  Programmer: haddox1 -- generated by xml2info
//  Creation:   Wed Jun 4 10:03:11 PDT 2003
//
//  Modifications:
//  David Camp, Thu May 23 12:52:53 PDT 2013
//  Remove the slicer and merger variable from the class. This was done for the
//  threading work. They are now created during execute.
//
// ****************************************************************************

avtThreeSliceFilter::avtThreeSliceFilter()
{
}


// ****************************************************************************
//  Method: avtThreeSliceFilter destructor
//
//  Programmer: haddox1 -- generated by xml2info
//  Creation:   Wed Jun 4 10:03:11 PDT 2003
//
//  Modifications:
//  David Camp, Thu May 23 12:52:53 PDT 2013
//  Remove the slicer and merger variable from the class. This was done for the
//  threading work. They are now created during execute.
//
// ****************************************************************************

avtThreeSliceFilter::~avtThreeSliceFilter()
{
}


// ****************************************************************************
//  Method:  avtThreeSliceFilter::Create
//
//  Programmer: haddox1 -- generated by xml2info
//  Creation:   Wed Jun 4 10:03:11 PDT 2003
//
// ****************************************************************************

avtFilter *
avtThreeSliceFilter::Create()
{
    return new avtThreeSliceFilter();
}


// ****************************************************************************
//  Method:      avtThreeSliceFilter::SetAtts
//
//  Purpose:
//      Sets the state of the filter based on the attribute object.
//
//  Arguments:
//      a        The attributes to use.
//
//  Programmer: haddox1 -- generated by xml2info
//  Creation:   Wed Jun 4 10:03:11 PDT 2003
//
// ****************************************************************************

void
avtThreeSliceFilter::SetAtts(const AttributeGroup *a)
{
    atts = *(const ThreeSliceAttributes*)a;
}


// ****************************************************************************
//  Method: avtThreeSliceFilter::Equivalent
//
//  Purpose:
//      Returns true if creating a new avtThreeSliceFilter with the given
//      parameters would result in an equivalent avtThreeSliceFilter.
//
//  Programmer: haddox1 -- generated by xml2info
//  Creation:   Wed Jun 4 10:03:11 PDT 2003
//
// ****************************************************************************

bool
avtThreeSliceFilter::Equivalent(const AttributeGroup *a)
{
    return (atts == *(ThreeSliceAttributes*)a);
}


// ****************************************************************************
//  Method: avtThreeSliceFilter::ExecuteData
//
//  Purpose:
//      Sends the specified input and output through the ThreeSlice filter.
//
//  Arguments:
//      in_dr      The input data representation.
//
//  Returns:       The output data representation.
//
//  Programmer: haddox1 -- generated by xml2info
//  Creation:   Wed Jun 4 10:03:11 PDT 2003
//
//  Modifications:
//
//    Hank Childs, Tue Jun 17 10:43:20 PDT 2003
//    Clean up memory leaks.
//
//    Kathleen Bonnell, Thu Jul  6 13:30:38 PDT 2006  
//    Fix to work with new vtk pipeline changes. 
//
//    Kathleen Bonnell, Wed Sep  6 14:20:59 PDT 2006 
//    Another fix for new vtk pipeline changes. 
//
//    Jeremy Meredith, Fri Oct  8 17:14:47 EDT 2010
//    ALWAYS set the cell list in vtkSlicer, even if it's NULL.  Since we 
//    keep the vtkSlicer around, it might have an old cell list from a
//    previous pass, and we need to clear it out if it's no longer valid.
//
//    David Camp, Thu May 23 12:52:53 PDT 2013
//    For threading, we create the vtkSlicer and vtkAppendPolyData object in
//    this function.
//
//    Eric Brugger, Tue Aug 19 09:30:56 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
//    Eric Brugger, Tue Aug 25 09:12:36 PDT 2015
//    Modified the routine to return NULL if the slice created a data set
//    with no cells. This fixes a bug where an error would be generated if
//    any of the domains being sliced resulted in no geometry.
//
// ****************************************************************************

avtDataRepresentation *
avtThreeSliceFilter::ExecuteData(avtDataRepresentation *in_dr)
{
    //
    // Get the VTK data set and domain number.
    //
    vtkDataSet *in_ds = in_dr->GetDataVTK();
    int domain = in_dr->GetDomain();

    float x = atts.GetX();
    float y = atts.GetY();
    float z = atts.GetZ();
    
    double bounds[6];
    in_ds->GetBounds(bounds);

    //
    // See which slices we have to do.
    // We need to do a certain plane if the free dimension (eg: z in XY)
    // is within the domain bounds.
    //
    
    const int XY = 0;
    const int XZ = 1;
    const int YZ = 2;
    bool doPlane[3];
    doPlane[XY] = (z >= bounds[4] && z <= bounds[5]);
    doPlane[XZ] = (y >= bounds[2] && y <= bounds[3]);
    doPlane[YZ] = (x >= bounds[0] && x <= bounds[1]);
    
    //
    // Check to see if we have to slice this domain at all.
    //
    
    if (!doPlane[XY] && !doPlane[XZ] && !doPlane[YZ])
    {
        debug5 << "Not slicing domain " << domain
               << ", it does not intersect the plane." << endl;
        return NULL;
    }

    vtkSlicer *slicer = vtkSlicer::New();
    slicer->SetOrigin(x,y,z);

    vtkIdType *cellList[3];
    vtkIdType nCells[3];

    cellList[0] = cellList[1] = cellList[2] = NULL;
    
    //
    // If we're dealing with a rectilinear grid, we should find 
    // the cells ourselves, since finding orthogonal slices is
    // so fast to calculate.
    //
    if (in_ds->GetDataObjectType() == VTK_RECTILINEAR_GRID)
    {
        vtkRectilinearGrid *rg = (vtkRectilinearGrid *) in_ds;
        
        int dims[3];
        rg->GetDimensions(dims);
        // Subtract one to get the cell dimensions from the point dimensions.
        --(dims[0]);
        --(dims[1]);
        --(dims[2]);

        int j;
        int ijk[3];
        double xyz[3];
        double pcoords[3];
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = z;

        //
        // We need to translate the point to the boundary if it is not
        // within it already.
        //
        // The ComputeStructuredCoordinates tends to fail on the boundries.
        // So if we have a point near the boundry, we'll jog it in
        // towards the dataset. 
        //
        
        for (int i = 0; i < 3; ++i)
        {
            double epsilon = (bounds[2 * i + 1] - bounds[i * 2]) 
                                / (16.0 * dims[i]);
            if (xyz[i] - epsilon < bounds[2 * i])
                xyz[i] = bounds[2 * i] + epsilon;
            else if (xyz[i] + epsilon > bounds[2 * i + 1])
                xyz[i] = bounds[2 * i + 1] - epsilon; 
        }
        
        rg->ComputeStructuredCoordinates(xyz, ijk, pcoords);
        
        if (doPlane[XY])
        {
            //
            // Find the cells for the xy plane:
            //   Cells are stored contiguously from 'start'.
            //

            vtkIdType start = ijk[2] * dims[0] * dims[1];
            nCells[0] = dims[0] * dims[1];
            cellList[0] = new vtkIdType[nCells[0]];
            for (vtkIdType i = 0; i < nCells[0]; ++i)
                cellList[0][i] = start + i;
        }

        if (doPlane[XZ])
        {
            //
            // Find the cells for the xz plane:
            //   Cells are stored in strips of dim[0], and those
            //   strips are offset by dims[0] * dims[1].
            //
            
            vtkIdType start = ijk[1] * dims[0];
            nCells[1] = dims[0] * dims[2];
            cellList[1] = new vtkIdType[nCells[1]];
            for (vtkIdType i = 0; i < nCells[1]; )
            {
                for (j = 0; j < dims[0]; ++j)
                {
                    cellList[1][i++] = start + j;
                }

                start += dims[0] * dims[1];
            }
        }
        
        if (doPlane[YZ])
        {
            //
            // Find the cells for the yz plane:
            //   Cells are stored from start offset by dims[0]
            //

            vtkIdType start = ijk[0];
            nCells[2] = dims[1] * dims[2];
            cellList[2] = new vtkIdType[nCells[2]];
            for (vtkIdType i = 0; i < nCells[2]; ++i)
                cellList[2][i] = start + (i * dims[0]);
        }
    }

    //
    // Fix up the plane orientation.
    //

    double dbounds[6];
    dbounds[0] = bounds[0];
    dbounds[1] = bounds[1];
    dbounds[2] = bounds[2];
    dbounds[3] = bounds[3];
    dbounds[4] = bounds[4];
    dbounds[5] = bounds[5];

    vtkAppendPolyData *merger = vtkAppendPolyData::New();

    vtkPolyData *out_ds[3];
    out_ds[0] = out_ds[1] = out_ds[2] = NULL;
    for (int i = 0; i < 3; ++i)
    {
        if (!doPlane[i])
        {
            continue;
        }
        slicer->SetCellList(cellList[i], nCells[i]);

        //
        // Set and fix the plane orientation.
        // i == 0 -> XY plane: (0, 0, 1)
        // i == 1 -> XZ plane: (0, 1, 0)
        // i == 2 -> YZ plane: (1, 0, 0)
        //
        slicer->SetNormal(i == 2, i == 1, i == 0);
        SetPlaneOrientation(dbounds, slicer);
        
        out_ds[i] = vtkPolyData::New();
    
        slicer->SetInputData(in_ds);
        slicer->Update();
        out_ds[i]->ShallowCopy(slicer->GetOutput());

        merger->AddInputData(out_ds[i]);
        if (cellList[i])
            delete[] cellList[i];
    }

    slicer->SetInputConnection(0,NULL);
    vtkPolyData *p = vtkPolyData::New();
    slicer->GetExecutive()->SetOutputData(0, p);
    p->Delete();

    vtkPolyData *rv = vtkPolyData::New();

    merger->Update();
    rv->ShallowCopy(merger->GetOutput());
    
    //
    // Clean up memory.
    //
    for (int i = 0; i < 3; ++i)
    {
        if (out_ds[i])
        {
            merger->RemoveInputData(out_ds[i]);
            out_ds[i]->Delete();
        }
    }    
    
    avtDataRepresentation *out_dr = NULL;
    if (rv->GetNumberOfCells() > 0)
    {
        out_dr = new avtDataRepresentation(rv,
            in_dr->GetDomain(), in_dr->GetLabel());
    }

    rv->Delete();

    slicer->Delete();
    merger->Delete();

    return out_dr;
}

// ****************************************************************************
//  Method: avtThreeSliceFilter::UpdateDataObjectInfo
//
//  Purpose:
//      Changes to topological dimension of the output to be one less that the
//      input.
//
//  Programmer: Akira Haddox
//  Creation:   June 4, 2003
//
//  Modifications:
//
//    Hank Childs, Mon May 24 08:42:53 PDT 2004
//    Allow normals to be calculated.
//
//    Kathleen Bonnell, Thu Mar  2 14:26:06 PST 2006 
//    Set ZonesSplit.
//
//    Brad Whitlock, Mon Apr  7 15:55:02 PDT 2014
//    Add filter metadata used in export.
//    Work partially supported by DOE Grant SC0007548.
//
// ****************************************************************************

void
avtThreeSliceFilter::UpdateDataObjectInfo(void)
{
    avtDataAttributes &inAtts      = GetInput()->GetInfo().GetAttributes();
    avtDataAttributes &outAtts     = GetOutput()->GetInfo().GetAttributes();
    avtDataValidity   &outValidity = GetOutput()->GetInfo().GetValidity();
   
    outAtts.SetTopologicalDimension(inAtts.GetTopologicalDimension()-1);
    outValidity.InvalidateZones();
    outValidity.ZonesSplit();

    char params[100];
    SNPRINTF(params, 100, "x=%lg, y=%lg, z=%lg", atts.GetX(), atts.GetY(), atts.GetZ());
    outAtts.AddFilterMetaData("ThreeSlice", params);
}


// ****************************************************************************
//  Method: avtThreeSliceFilter::ReleaseData
//
//  Purpose:
//      Release the data associated with a pipeline.
//
//  Programmer: Hank Childs
//  Creation:   June 17, 2003
//
//  Modifications:
//
//    Hank Childs, Fri Mar  4 08:12:25 PST 2005
//    Do not set outputs of filters to NULL, since this will prevent them
//    from re-executing correctly in DLB-mode.
//
//    Hank Childs, Fri Mar 11 07:37:05 PST 2005
//    Fix non-problem size leak introduced with last fix.
//
//    David Camp, Thu May 23 12:52:53 PDT 2013
//    Remove the slicer and merger variable from the class. This was done for the
//    threading work. They are now created during execute.
//
// ****************************************************************************

void
avtThreeSliceFilter::ReleaseData(void)
{
    avtPluginDataTreeIterator::ReleaseData();
}


// ****************************************************************************
//  Method: avtThreeSliceFilter::SetPlaneOrientation
//
//  Purpose:
//      The VTK slicing routines will sometimes not slice correctly when the
//      slice coincides with a face of a cell.  If this face is on the
//      boundary, we sometimes get no intersecting triangles.  To counteract
//      this, we can set the plane to be the plane with the direct opposite
//      normal. We assume that the plane has a normal either in the positive
//      x, y, or z direction.
//
//  Arguments:
//      b       The bounding box of the dataset.
//      slicer  The slicer of this dataset.
//      
//  Programmer: Akira Haddox
//  Creation:   June 10, 2003
//
//  Modifications:
//  David Camp, Thu May 23 12:52:53 PDT 2013
//  For threading, we now pass the vtkSlice object into the function.
//
// ****************************************************************************

void
avtThreeSliceFilter::SetPlaneOrientation(double *b, vtkSlicer *slicer)
{
    double normal[3];
    normal[0] = slicer->GetNormal()[0];
    normal[1] = slicer->GetNormal()[1];
    normal[2] = slicer->GetNormal()[2];

    //
    // Because of the underlying implementation, we will run into cases where
    // there is no slice if it intersects the cell on the face.  Try to 
    // counter-act this.
    //
    double ox = slicer->GetOrigin()[0];
    double oy = slicer->GetOrigin()[1];
    double oz = slicer->GetOrigin()[2];
    if (normal[0] > 0.)
    {
        if (ox == b[0])
        {
            slicer->SetNormal(-normal[0], -normal[1], -normal[2]);
        }
    }
    else if (normal[1] > 0.)
    {
        if (oy == b[2])
        {
            slicer->SetNormal(-normal[0], -normal[1], -normal[2]);
        }
    }
    else if (normal[2] > 0.)
    {
        if (oz == b[4])
        {
            slicer->SetNormal(-normal[0], -normal[1], -normal[2]);
        }
    }
}

