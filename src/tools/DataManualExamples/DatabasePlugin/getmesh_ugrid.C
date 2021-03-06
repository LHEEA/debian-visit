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

// NOTE - This code incomplete and requires underlined portions
// to be replaced with code to read values from your file format.

#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <InvalidVariableException.h>

vtkDataSet *
avtXXXFileFormat::GetMesh(const char *meshname)
{
    int ndims = 2;
    int nnodes, ncells, origin = 1;
    
    // Read the ndims, nnodes, ncells, origin from file.
    ndims = NUMBER OF MESH DIMENSIONS;
    nnodes = NUMBER OF NODES IN THE MESH;
    ncells = NUMBER OF CELLS IN THE MESH;
    origin = GET THE ORIGIN (0 or 1);

    // Read the X coordinates from the file.
    float *xarray = new float[nnodes];
    READ nnodes FLOAT VALUES INTO xarray

    // Read the Y coordinates from the file.
    float *yarray = new float[nnodes];
    READ nnodes FLOAT VALUES INTO yarray

    // Read the Z coordinates from the file.
    float *zarray = 0;
    if(ndims > 2)
    {
        zarray = new float[nnodes];
        READ dims[2] FLOAT VALUES INTO zarray
    }

    // Read in the connectivity array. This example assumes that
    // the connectivity will be stored: type, indices, type,
    // indices, ... and that there will be a type/index list
    // pair for each cell in the mesh.
    int *connectivity = 0;
    ALLOCATE connectivity ARRAY AND READ VALUES INTO IT.

    //
    // Create the vtkPoints object and copy points into it.
    //
    vtkPoints *points = vtkPoints::New();
    points->SetNumberOfPoints(nnodes);
    float *pts = (float *) points->GetVoidPointer(0);
    float *xc = xarray;
    float *yc = yarray;
    float *zc = zarray;
    if(ndims == 3)
    {
        for(int i = 0; i < nnodes; ++i)
        {
            *pts++ = *xc++;
            *pts++ = *yc++;
            *pts++ = *zc++;
        }
    }
    else if(ndims == 2)
    {
        for(int i = 0; i < nnodes; ++i)
        {
            *pts++ = *xc++;
            *pts++ = *yc++;
            *pts++ = 0.;
        }
    }

    // Delete temporary arrays.
    delete [] xarray;
    delete [] yarray;
    delete [] zarray;

    //
    // Create a vtkUnstructuredGrid to contain the point cells.
    //
    vtkUnstructuredGrid *ugrid = vtkUnstructuredGrid::New(); 
    ugrid->SetPoints(points);
    points->Delete();
    ugrid->Allocate(ncells);
    vtkIdType verts[8];
    int *conn = connectivity
    for(int i = 0; i < ncells; ++i)
    {
        int fileCellType = *conn++;

        // You file's cellType will likely not match so you
        // will have to translate fileCellType to a VTK
        // cell type.
        int cellType = MAP fileCellType TO VTK CELL TYPE.

        // Determine number of vertices for each cell type.
        if(cellType == VTK_VERTEX)
            nverts = 1;
        else if(cellType == VTK_LINE)
            nverts = 2;
        else if(cellType == VTK_TRIANGLE)
            nverts = 3;
        else if(cellType == VTK_QUAD)
            nverts = 4;
        else if(cellType == VTK_TETRA)
            nverts = 4;
        else if(cellType == VTK_PYRAMID)
            nverts = 5;
        else if(cellType == VTK_WEDGE)
            nverts = 6;
        else if(cellType == VTK_HEXAHEDRON)
            nverts = 8;
        else
        {
            delete [] connectivity;
            ugrid->Delete();
            // Other cell type - need to add a case for it.
            // In the meantime, throw exception or if you
            // know enough, skip the cell.
            EXCEPTION0(InvalidVariableException, meshname);
        }

        // Make a list of node indices that make up the cell.
        for(int j = 0; j < nverts; ++j)
            verts[j] = conn[j] - origin;
        conn += nverts;

        // Insert the cell into the mesh.
        ugrid->InsertNextCell(cellType, nverts, verts);
    }

    delete [] connectivity;

    return ugrid;
}
