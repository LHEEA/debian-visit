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
//                            avtWatertightQuery.C                           //
// ************************************************************************* //

#include <avtWatertightQuery.h>

#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkDataSet.h>
#include <vtkPointData.h>

#include <avtFindExternalExpression.h>
#include <avtSourceFromAVTDataset.h>
#include <InvalidDimensionsException.h>
#include <InvalidVariableException.h>

#include <avtParallel.h>

using     std::string;

// ****************************************************************************
//  Method: avtWatertightQuery constructor
//
//  Programmer: Hank Childs 
//  Creation:   September 23, 2005 
//
//  Modifications:
//
//    Hank Childs, Fri Feb  4 14:33:41 PST 2011
//    Reflect new name for expression to find external cells.
//
// ****************************************************************************

avtWatertightQuery::avtWatertightQuery() 
{
    external_nodes = new avtFindExternalExpression;
    external_nodes->SetDoCells(false);
    external_nodes->SetOutputVariableName("_avt_external_nodes");
}


// ****************************************************************************
//  Method: avtWatertightQuery destructor
//
//  Programmer: Hank Childs 
//  Creation:   September 23, 2005 
//
//  Modifications:
//
// ****************************************************************************

avtWatertightQuery::~avtWatertightQuery()
{
    if (external_nodes != NULL)
    {
        delete external_nodes;
        external_nodes = NULL;
    }
}


// ****************************************************************************
//  Method: avtWatertightQuery::VerifyInput 
//
//  Purpose:  Throw exception for invalid input. 
//
//  Programmer: Hank Childs 
//  Creation:   September 23, 2005
//
// ****************************************************************************

void 
avtWatertightQuery::VerifyInput()
{
    //
    //  Since base class performs general input verification for all queries,
    //  make sure to call it's verify method first.
    //
    avtDataObjectQuery::VerifyInput();

    int tDim = GetInput()->GetInfo().GetAttributes().GetTopologicalDimension();
    if  (tDim != 2)
    {
        EXCEPTION2(InvalidDimensionsException, "Watertight query", 
                   "3D surface");
    }
}


// ****************************************************************************
//  Method: avtWatertightQuery::ApplyFilters 
//
//  Purpose:  Apply any avt filters necessary for completion of this query.
//
//  Programmer: Hank Childs 
//  Creation:   September 23, 2005 
//
// ****************************************************************************

avtDataObject_p 
avtWatertightQuery::ApplyFilters(avtDataObject_p inData)
{
    avtContract_p contract =
        inData->GetOriginatingSource()->GetGeneralContract();

    //
    // Create an artificial pipeline.
    //
    avtDataset_p ds;
    CopyTo(ds, inData);
    avtSourceFromAVTDataset termsrc(ds);
    avtDataObject_p dob = termsrc.GetOutput();
    external_nodes->SetInput(dob);
    avtDataObject_p objOut = external_nodes->GetOutput();
    objOut->Update(contract);
    return objOut;
}



// ****************************************************************************
//  Method: avtWatertightQuery::PreExecute
//
//  Purpose:
//      This is called before all of the domains are executed.
//
//  Programmer: Hank Childs
//  Creation:   September 23, 2005
//
//  Modifications:
//    Jeremy Meredith, Thu Feb 15 11:55:03 EST 2007
//    Call inherited PreExecute before everything else.
//
// ****************************************************************************

void
avtWatertightQuery::PreExecute(void)
{
    avtDatasetQuery::PreExecute();

    foundExternalNode = false;
}



// **************************************************************************** //  Method: avtWatertightQuery::PostExecute
//
//  Purpose:
//      This is called after all of the domains are executed.
//
//  Programmer: Hank Childs
//  Creation:   September 23, 2005
//
//  Modifications:
//    Kathleen Biagas, Tue Feb 25 10:33:31 PST 2014
//    Add XML results.
//
// ****************************************************************************


void
avtWatertightQuery::PostExecute(void)
{
    int boolAsInt = (int) foundExternalNode;
    boolAsInt = UnifyMaximumValue(boolAsInt);
    foundExternalNode = (boolAsInt > 0);

    char buf[1024];
    if (foundExternalNode)
    {
        strcpy(buf, "The surface is not watertight.  To identify the regions "
                  "that are not watertight, perform the following steps:\n"
                  "\t1) Define the expression: \"external_node(meshname)\"\n"
                  "\t2) If some set of operations have been performed on the "
                  "mesh, then you will need to turn on the DeferExpression \n"
                  "\toperator under Options->Plugin Manager and then apply "
                  "this operator with the external node expression to your "
                  "plot.\n"
                  "\t3) Change the variable you are plotting by to the "
                  "external nodes expression.  This will show where the \n"
                  "\tnon-watertight nodes are located.\n");
    }
    else
    {
        strcpy(buf, "The surface is watertight.");
    }

    //
    //  Parent class uses this message to set the Results message
    //  in the Query Attributes that is sent back to the viewer.
    //  That is all that is required of this query.
    //
    SetResultMessage(buf);
    SetResultValue(foundExternalNode);
    MapNode result_node;
    result_node["watertight"] = foundExternalNode;
    SetXmlResult(result_node.ToXML());
}


// ****************************************************************************
//  Method: avtWatertightQuery::Execute
//
//  Purpose:
//      Processes a single domain.
//
//  Programmer: Hank Childs
//  Creation:   September 23, 2005
//
// ****************************************************************************

void
avtWatertightQuery::Execute(vtkDataSet *ds, const int dom)
{
    vtkDataArray *arr = ds->GetPointData()->GetArray("_avt_external_nodes");
    if (arr == NULL)
        arr = ds->GetCellData()->GetArray("_avt_external_nodes");

    if (arr == NULL)
        EXCEPTION1(InvalidVariableException, "_avt_external_nodes");

    int nValues = arr->GetNumberOfTuples();
    for (int i = 0 ; i < nValues ; i++)
    {
        float val = arr->GetTuple1(i);
        if (val != 0.)
            foundExternalNode = true;
    }
}


