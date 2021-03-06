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
//                          avtConnCMFEExpression.C                          //
// ************************************************************************* //

#include <avtConnCMFEExpression.h>

#include <math.h>

#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkDataSet.h>
#include <vtkPointData.h>
#include <vtkLongArray.h>

#include <avtSILRestrictionTraverser.h>

#include <DebugStream.h>
#include <InvalidMergeException.h>
#include <snprintf.h>


// ****************************************************************************
//  Method: avtConnCMFEExpression constructor
//
//  Purpose:
//      Defines the constructor.  Note: this should not be inlined in the
//      header because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   August 26, 2005
//
// ****************************************************************************

avtConnCMFEExpression::avtConnCMFEExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtConnCMFEExpression destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   August 26, 2005
//
// ****************************************************************************

avtConnCMFEExpression::~avtConnCMFEExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtConnCMFEExpression::PerformCMFE
//
//  Purpose:
//      Performs a cross-mesh field evaluation based on connectivity
//      differencing.
//
//  Programmer: Hank Childs
//  Creation:   August 26, 2005
// 
// ****************************************************************************

avtDataTree_p
avtConnCMFEExpression::PerformCMFE(avtDataTree_p in1, avtDataTree_p in2,
                                   const std::string &invar,
                                   const std::string &outvar)
{
    avtDataTree_p outtree = ExecuteTree(in1, in2, invar, outvar);
    return outtree;
}


// ****************************************************************************
//  Method: avtConnCMFEExpression::ExecuteTree
// 
//  Purpose:
//      Executes a data tree for the ConnCMFE expression.
//
//  Programmer: Hank Childs
//  Creation:   August 26, 2005
//
//  Modifications:
//
//    Hank Childs, Fri Oct  7 11:07:33 PDT 2005
//    Modify warning message to account for material selection.
//
//    Cyrus Harrison, Tue Mar 27 15:37:22 PDT 200
//    Fixed unreachable else statement and incorrect error message
//
//    Hank Childs, Sun Mar 22 14:13:16 CDT 2009
//    Beef up debug statements in exception case.
//
// ****************************************************************************

avtDataTree_p
avtConnCMFEExpression::ExecuteTree(avtDataTree_p in1, avtDataTree_p in2,
                                   const std::string &invar,
                                   const std::string &outvar)
{
    int numNull = 0;
    if (*in1 == NULL)
        numNull++;
    if (*in2 == NULL)
        numNull++;
    if (numNull == 2)
        return NULL;

    debug5 << "avtConnCMFEExpression::ExecuteTree: numNull=" << numNull << std::endl;
    if (numNull == 1)
        EXCEPTION1(InvalidMergeException, "The databases cannot be compared "
                   "because they have a different number of domains.");

    int nc1 = in1->GetNChildren();
    int nc2 = in1->GetNChildren();

    debug5 << "avtConnCMFEExpression::ExecuteTree: nc1=" << nc1 << " nc2= " << nc2 << std::endl;
    if (nc1 != nc2)
        EXCEPTION1(InvalidMergeException, "The databases cannot be compared "
                   "because they have a different number of domains.");

    if (nc1 <= 0)
    {
        int numHaveData = 0;
        if (in1->HasData())
            numHaveData++;
        if (in2->HasData())
            numHaveData++;
        debug5 << "avtConnCMFEExpression::ExecuteTree: numHaveData " << numHaveData << std::endl;
        if (numHaveData == 1)
            EXCEPTION1(InvalidMergeException, "The databases cannot be "
                  "compared because they have a different number of domains.");
        if (numHaveData == 0)
            return NULL;

        // 
        // We finally get to get their VTK datasets and compare them.
        //
        vtkDataSet *in_ds1 = in1->GetDataRepresentation().GetDataVTK();
        vtkDataSet *in_ds2 = in2->GetDataRepresentation().GetDataVTK();

        //
        // Make some basic checks to make sure the connectivities really do
        // agree.
        //
        char msg[1024];
        if (in_ds1->GetNumberOfCells() != in_ds2->GetNumberOfCells())
        {
            avtSILRestrictionTraverser trav(firstDBSIL);
            if (trav.UsesAllMaterials())
            {
                SNPRINTF(msg, 1024,
                             "The databases cannot be compared because they "
                             "have a different number of cells for domain %d."
                             " The cell counts are %d and %d.",
                             in1->GetDataRepresentation().GetDomain(),
                             static_cast<int>(in_ds1->GetNumberOfCells()),
                             static_cast<int>(in_ds2->GetNumberOfCells()));
            }
            else
            {
                SNPRINTF(msg, 1024,
                             "The databases cannot be compared because they"
                             " have a different number of cells for domain %d."
                             " The cell counts are %d and %d.  It appears that"
                             " you have removed some materials.  Databases "
                             "cannot be compared in this manner when materials"
                             " have been removed (and the simulation is "
                             "Eulerian).",
                             in1->GetDataRepresentation().GetDomain(),
                             static_cast<int>(in_ds1->GetNumberOfCells()), 
                             static_cast<int>(in_ds2->GetNumberOfCells()));
            }
            EXCEPTION1(InvalidMergeException, msg);
        }
        if (in_ds1->GetNumberOfPoints() != in_ds2->GetNumberOfPoints())
        {
            avtSILRestrictionTraverser trav(firstDBSIL);
            if (trav.UsesAllMaterials())
            {
                SNPRINTF(msg, 1024,
                             "The databases cannot be compared because they "
                             "have a different number of points for domain %d."
                             "  The point counts are %d and %d.", 
                         in1->GetDataRepresentation().GetDomain(),
                         static_cast<int>(in_ds1->GetNumberOfPoints()), 
                         static_cast<int>(in_ds2->GetNumberOfPoints()));
            }
            else
            {
                SNPRINTF(msg, 1024,
                             "The databases cannot be compared because they "
                             "have a different number of points for domain %d."
                             "  The point counts are %d and %d.  It appears "
                             "that you have removed some materials.  Databases"
                             " cannot be compared in this manner when materials"
                             " have been removed (and the simulation is "
                             "Eulerian).",
                         in1->GetDataRepresentation().GetDomain(),
                         static_cast<int>(in_ds1->GetNumberOfPoints()), 
                         static_cast<int>(in_ds2->GetNumberOfPoints()));
            }
            EXCEPTION1(InvalidMergeException, msg);
        }

        bool isPoint      = true;
        vtkDataArray *arr = NULL;
        arr               = in_ds2->GetPointData()->GetArray(invar.c_str());
        if (arr == NULL)
        {
            arr     = in_ds2->GetCellData()->GetArray(invar.c_str());
            isPoint = false;
        }
        if (arr == NULL)
        {
            sprintf(msg, "The databases cannot be compared because variable "
                         " \"%s\" cannot be located.", invar.c_str());
            EXCEPTION1(InvalidMergeException, msg);
        }

        // 
        // At this point copy field data from the second data set to
        // the first data set. This is a backdoor method for time
        // varying fields and moving higher element data that is
        // stored in the field data.
        //
        vtkFieldData *fd1 = in_ds1->GetFieldData();
        vtkFieldData *fd2 = in_ds2->GetFieldData();

        if( fd1->GetNumberOfArrays() && fd2->GetNumberOfArrays() )
        {
          for( int i=0; i<fd1->GetNumberOfArrays(); ++i )
          {
            // Copy only arrays found in both datasets.
            const char *name1 = fd1->GetArrayName(i);
            vtkAbstractArray *fp2 = fd2->GetAbstractArray(name1);
        
            if( fp2 )
            {
              // Make a copy of the array found in dataset2
              vtkAbstractArray *fp = (vtkAbstractArray *) fp2->NewInstance();
              fp->DeepCopy( fp2 );

              // Append '2' to the name so not to have any name conflicts.
              char name[128];
              sprintf( name, "%s2", name1);

              fp->SetName(name);
              in_ds1->GetFieldData()->AddArray(fp);
              fp->Delete();
            }
          }
        }

        //
        // 
        //
        vtkDataArray *addvar = NULL;
        bool deleteAddvar = false;
        if (invar == outvar)
        {
            addvar       = arr;
            deleteAddvar = false;
        }
        else
        {
            addvar = arr->NewInstance();
            addvar->DeepCopy(arr);
            addvar->SetName(outvar.c_str());
            deleteAddvar = true;
        }
        
        vtkDataSet *new_obj = (vtkDataSet *) in_ds1->NewInstance();
        new_obj->ShallowCopy(in_ds1);
        if (isPoint)
            new_obj->GetPointData()->AddArray(addvar);
        else
            new_obj->GetCellData()->AddArray(addvar);
        if (deleteAddvar)
            addvar->Delete();
        avtDataTree_p rv = new avtDataTree(new_obj, 
                                      in1->GetDataRepresentation().GetDomain(),
                                      in1->GetDataRepresentation().GetLabel());
        new_obj->Delete();
        return rv;
    }
    else
    {
        //
        // There is more than one input dataset to process
        // and we need an output datatree for each.
        //
        avtDataTree_p *outDT = new avtDataTree_p[nc1];
        for (int j = 0; j < nc1; j++)
        {
            int numPresent = 0;
            if (in1->ChildIsPresent(j))
                numPresent++;
            if (in2->ChildIsPresent(j))
                numPresent++;
            if (numPresent == 0)
            {
                outDT[j] = NULL;
            }
            else if (numPresent == 2)
            {
                outDT[j] = ExecuteTree(in1->GetChild(j), in2->GetChild(j), 
                                       invar, outvar);
            }
            else
            {
                debug1 << "Number of children = " << nc1 << endl;
                debug1 << "In1(j) " << (int) in1->ChildIsPresent(j) << endl;
                debug1 << "In2(j) " << (int) in2->ChildIsPresent(j) << endl;
                EXCEPTION1(InvalidMergeException, "The databases cannot be "
                  "compared because they have a different number of domains.");
            }
        }
        avtDataTree_p rv = new avtDataTree(nc1, outDT);
        delete [] outDT;
        return (rv);
    }
}
