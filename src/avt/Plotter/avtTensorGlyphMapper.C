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
//                             avtTensorGlyphMapper.C                        //
// ************************************************************************* //

#include <avtTensorGlyphMapper.h>

#include <vtkActor.h>
#include <vtkAlgorithmOutput.h>
#include <vtkDataSetMapper.h>
#include <vtkLookupTable.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkVisItTensorGlyph.h>
#include <vtkVisItPolyDataNormals.h>

#include <avtExtents.h>

#include <BadIndexException.h>



// ****************************************************************************
//  Method: avtTensorGlyphMapper constructor
//
//  Arguments:
//      g       The glyph this mapper should use.
//
//  Programmer: Hank Childs
//  Creation:   September 23, 2003
//
//  Modifications:
//
//    Hank Childs, Wed May  5 14:19:54 PDT 2004
//    Added poly data normals.
//
//    Eric Brugger, Wed Nov 24 13:04:09 PST 2004
//    Added scaleByMagnitude and autoScale.
//
//    Kathleen Biagas, Thu Feb 7 08:45:03 PST 2013
//    Changed arg to vtkAlgorithmOutput for pipeline connections with VTK v 6.
//
//    Kathleen Biagas, Thu Feb 7 12:58:49 PST 2013
//    We don't want to own glyph, so don't up the ref count.
//
//    Kathleen Biagas, Thu Mar 14 13:04:18 PDT 2013
//    Remove normalsFilter.
//
// ****************************************************************************

avtTensorGlyphMapper::avtTensorGlyphMapper(vtkAlgorithmOutput *g)
{
    glyph = g;

    colorByMag        = true;
    scale             = 0.2;
    scaleByMagnitude  = true;
    autoScale         = true;
    tensorFilter      = NULL;
    nTensorFilters    = 0;
    lut = NULL;
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper destructor
//
//  Programmer: Hank Childs
//  Creation:   September 23, 2003
//
//  Modifications:
//
//    Hank Childs, Wed May  5 14:19:54 PDT 2004
//    Deleted poly data normals.
//
//    Kathleen Biagas, Thu Feb 7 12:58:49 PST 2013
//    We don't own glyph, so don't delete it here.
//
//    Kathleen Biagas, Thu Mar 14 13:04:18 PDT 2013
//    Remove normalsFilter.
//
// ****************************************************************************

avtTensorGlyphMapper::~avtTensorGlyphMapper()
{
    if (tensorFilter != NULL)
    {
        for (int i = 0 ; i < nTensorFilters ; i++)
        {
            if (tensorFilter[i] != NULL)
            {
                tensorFilter[i]->Delete();
            }
        }
        delete [] tensorFilter;
    }
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper::CustomizeMappers
//
//  Purpose:
//      A hook from the base class that allows the variable mapper to force
//      the vtk mappers to be the same as its state.
//
//  Programmer: Hank Childs
//  Creation:   September 23, 2003
//
//  Modifications:
//
//    Hank Childs, Wed May  5 14:19:54 PDT 2004
//    Added poly data normals.
//
//    Eric Brugger, Wed Nov 24 13:04:09 PST 2004
//    Added scaleByMagnitude and autoScale.
//
//    Kathleen Biagas, Thu Feb 7 08:46:37 PST 2013
//    Set the SourceConnection to the tensorFilter, not SourceData.
//
//    Kathleen Biagas, Thu Mar 14 13:04:18 PDT 2013
//    Remove normalsFilter.
//
// ****************************************************************************

void
avtTensorGlyphMapper::CustomizeMappers(void)
{
    if (tensorFilter != NULL)
    {
        for (int i = 0 ; i < nTensorFilters ; i++)
        {
            if (tensorFilter[i] != NULL)
            {
                tensorFilter[i]->SetSourceConnection(glyph);
                if (scaleByMagnitude)
                    tensorFilter[i]->SetScaling(1);
                else
                    tensorFilter[i]->SetScaling(0);
            }
        }
    }
         
    if (colorByMag)
    {
        ColorByMagOn();
    }
    else
    {
        ColorByMagOff(glyphColor);
    }

    for (int i = 0; i < nMappers; i++)
    {
        if (actors[i] != NULL) 
        {
            mappers[i]->SetLookupTable(lut);
        }
    }

    SetScale(scale);
    SetDefaultRange();
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper::SetUpFilters
//
//  Purpose:
//      The glyph mapper inserts filters into the VTK pipeline, but can
//      only do so inside another routines (avtMapper::SetUpMappers) loop.
//      This is called before InsertFilters to allow for initialization work.
//
//  Programmer: Hank Childs
//  Creation:   September 23, 2003
//
//  Modifications:
//
//    Hank Childs, Wed May  5 14:19:54 PDT 2004
//    Added poly data normals.
//
//    Kathleen Bonnell, Tue Aug 30 15:11:01 PDT 2005 
//    Use VisIt version of TensorGlyph, so that original cell and node
//    arrays can be copied through. 
//
//    Kathleen Biagas, Thu Mar 14 13:04:18 PDT 2013
//    Remove normalsFilter.
//
// ****************************************************************************

void
avtTensorGlyphMapper::SetUpFilters(int nDoms)
{
    if (tensorFilter != NULL)
    {
        for (int i = 0 ; i < nTensorFilters ; i++)
        {
            if (tensorFilter[i] != NULL)
            {
                tensorFilter[i]->Delete();
            }
        }
        delete [] tensorFilter;
    }

    nTensorFilters     = nDoms;
    tensorFilter       = new vtkVisItTensorGlyph*[nTensorFilters];
    for (int i = 0 ; i < nTensorFilters ; i++)
    {
        tensorFilter[i] = NULL;
    }
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper::InsertFilters
//
//  Purpose:
//      Inserts a glyph filter into the vtk Pipeline.
//
//  Arguments:
//      ds        The upstream dataset.
//      dom       The domain number.
//      mode      The rendering mode.
//
//  Returns:      The dataset to be sent downstream.
//
//  Programmer: Hank Childs
//  Creation:   September 23, 2003
//
//  Modifications:
//
//    Hank Childs, Wed May  5 14:19:54 PDT 2004
//    Added poly data normals.
//
//    Jeremy Meredith, Tue Jun  1 11:24:29 PDT 2004
//    Only do the normals if in 3-space.
//
//    Kathleen Bonnell, Tue Aug 30 15:11:01 PDT 2005 
//    Use VisIt version of TensorGlyph, so that original cell and node
//    arrays can be copied through. 
//
//    Kathleen Biagas, Wed Feb 6 19:38:27 PDT 2013
//    Changed signature of InsertFilters.
//
//    Kathleen Biagas, Thu Mar 14 13:04:18 PDT 2013
//    Remove normalsFilter.
//
// ****************************************************************************

vtkAlgorithmOutput *
avtTensorGlyphMapper::InsertFilters(vtkDataSet *ds, int dom)
{
    if (dom < 0 || dom >= nTensorFilters)
    {
        EXCEPTION2(BadIndexException, dom, nTensorFilters);
    }

    if (tensorFilter[dom] == NULL)
    {
        //
        // We don't have to initialize the filter now, since it will be done
        // in customize mappers later.
        //
        tensorFilter[dom] = vtkVisItTensorGlyph::New();
    }

    tensorFilter[dom]->SetInputData(ds);
    return tensorFilter[dom]->GetOutputPort();
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper::SetScale
//
//  Purpose:
//      Sets the scale of each glyph.
//
//  Arguments:
//      s        The new scale.
//
//  Programmer:  Hank Childs 
//  Creation:    September 23, 2003 
//
//  Modifications:
//
//    Hank Childs, Fri May  7 07:38:31 PDT 2004
//    Reset the default range so the colors update properly.
//
//    Eric Brugger, Wed Nov 24 13:04:09 PST 2004
//    Added scaleByMagnitude and autoScale.
//
//    Hank Childs, Thu Aug 26 13:47:30 PDT 2010
//    Change extents names.
//
// ****************************************************************************

void
avtTensorGlyphMapper::SetScale(double s)
{
    scale = s;

    //
    // If auto scale is enable, then set the scale based on the spatial
    // extents and possibly the data extents.
    //
    if (autoScale)
    {
        avtDataset_p input = GetTypedInput();
        if (*input != 0)
        {
            avtDataAttributes &atts=input->GetInfo().GetAttributes();
            avtExtents *extents = atts.GetOriginalSpatialExtents();
            int nDims = extents->GetDimension();
            double exts[6];
            extents->CopyTo(exts);
            double dist = 0.;
            int i;
            for (i = 0; i < nDims; i++)
            {
                dist += (exts[2*i+1] - exts[2*i]) * (exts[2*i+1] - exts[2*i]);
            }
            dist = sqrt(dist);

            extents = atts.GetOriginalDataExtents();
            extents->CopyTo(exts);

            if (scaleByMagnitude)
                scale = (scale * dist * 0.2) / exts[1];
            else
                scale = scale * dist * 0.2;
        }
    }

    if (tensorFilter != NULL)
    {
        for (int i = 0 ; i < nTensorFilters ; i++)
        {
            if (tensorFilter[i] != NULL)
            {
                tensorFilter[i]->SetScaleFactor(scale);
            }
        }
    }

    SetDefaultRange();
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper::SetScaleByMagnitude
//
//  Purpose:
//      Sets the scale by magnitude mode.
//
//  Arguments:
//      val      The new scale by magnitude mode.
//
//  Programmer:  Eric Brugger
//  Creation:    November 24, 2004
//
// ****************************************************************************

void
avtTensorGlyphMapper::SetScaleByMagnitude(bool val)
{
    scaleByMagnitude = val;

    if (tensorFilter != NULL)
    {
        for (int i = 0 ; i < nTensorFilters ; i++)
        {
            if (tensorFilter[i] != NULL)
            {
                if (scaleByMagnitude)
                    tensorFilter[i]->SetScaling(1);
                else
                    tensorFilter[i]->SetScaling(0);
            }
        }
    }
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper::SetAutoScale
//
//  Purpose:
//      Sets the auto scale mode.
//
//  Arguments:
//      val      The new auto scale mode.
//
//  Programmer:  Eric Brugger
//  Creation:    November 24, 2004
//
// ****************************************************************************

void
avtTensorGlyphMapper::SetAutoScale(bool val)
{
    autoScale = val;
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper::ColorByMagOn
//
//  Purpose:
//      Tells the glyph mapper to color by the magnitude.
//
//  Programmer: Hank Childs
//  Creation:   September 23, 2003
//
// ****************************************************************************

void
avtTensorGlyphMapper::ColorByMagOn(void)
{
    colorByMag = true;

    if (tensorFilter != NULL)
    {
        for (int i = 0 ; i < nTensorFilters ; i++)
        {
            if (tensorFilter[i] != NULL)
            {
                tensorFilter[i]->SetColorModeToEigenvalues();
            }
        }
    }
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper::ColorByMagOff
//
//  Purpose:
//      Tells the glyph mapper to color all of the glyphs the same color.
//
//  Arguments:
//      col       The new color.
//
//  Programmer:   Hank Childs
//  Creation:     September 23, 2003
//
// ****************************************************************************

void
avtTensorGlyphMapper::ColorByMagOff(const unsigned char col[3])
{
    glyphColor[0] = col[0];
    glyphColor[1] = col[1];
    glyphColor[2] = col[2];
    colorByMag = false;
  
    if (actors != NULL)
    {
        for (int i = 0 ; i < nMappers ; i++)
        {
            if (actors[i] != NULL)
            {
                vtkProperty *prop = actors[i]->GetProperty();
                double r = ((double) glyphColor[0]) / 255.;
                double g = ((double) glyphColor[1]) / 255.;
                double b = ((double) glyphColor[2]) / 255.;
                prop->SetColor(r, g, b);
            }
        }
    }

    if (tensorFilter != NULL)
    {
        for (int i = 0 ; i < nTensorFilters ; i++)
        {
            if (tensorFilter[i] != NULL)
            {
                tensorFilter[i]->SetColorModeToScalars();
            }
        }
    }
}


// ****************************************************************************
//  Method: avtTensorGlyphMapper::SetLookupTable
//
//  Purpose: 
//      Replaces the current lookup table. 
//
//  Arguments:
//   LUT       The new lookup table to be used. 
//
//  Programmer: Hank Childs 
//  Creation:   September 23, 2003
//
// ****************************************************************************

void
avtTensorGlyphMapper::SetLookupTable(vtkLookupTable *LUT)
{
    if (lut == LUT)
    {
        // no need to change anything
        return;
    }
    lut = LUT;

    // Replace each mapper's lut.
    for (int i = 0 ; i < nMappers ; i++)
    {
        if (actors[i] != NULL)
        {
            mappers[i]->SetLookupTable(lut);
        }
    } 
}


