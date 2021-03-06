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
//                         avtConstantCreatorExpression.C                    //
// ************************************************************************* //

#include <avtConstantCreatorExpression.h>

#include <vtkDataArray.h>
#include <vtkFloatArray.h>


// ****************************************************************************
//  Method: avtConstantCreatorExpression constructor
//
//  Purpose:
//      Defines the constructor.  Note: this should not be inlined in the
//      header because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
// ****************************************************************************

avtConstantCreatorExpression::avtConstantCreatorExpression()
{
    value = 0;
    isSingleton = true;
}


// ****************************************************************************
//  Method: avtConstantCreatorExpression destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
// ****************************************************************************

avtConstantCreatorExpression::~avtConstantCreatorExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtConstantCreatorExpression::DoOperation
//
//  Purpose:
//      Generates new constants.
//
//  Arguments:
//      in            The input data array (ignored).
//      out           The output data array.
//      ncomponents   The number of components ('1' for scalar, '2' or '3' for
//                    vectors, etc.)
//      ntuples       The number of tuples (ie 'npoints' or 'ncells')
//
//  Programmer: Sean Ahern
//  Creation:   Sat Feb 22 00:42:35 America/Los_Angeles 2003
//
//  Modifications:
//
// ****************************************************************************
 
void
avtConstantCreatorExpression::DoOperation(vtkDataArray *, vtkDataArray *out,
                                      int ncomponents, int ntuples)
{
    for (int i = 0 ; i < ntuples ; i++)
        out->SetTuple1(i, value);
}


// ****************************************************************************
//  Method: avtConstantCreatorExpression::CreateArray
//
//  Purpose:
//      Creates an array of constant value.  Note that this routine will not
//      return uchar arrays.  The motivation for this is that most uchar arrays
//      come from the conditional expression (if), which uses a uchar as the
//      conditional, but really wants floats as the then- and else- variables.
//      (ie if(gt(X, 2.), 1., 0.) -- the constant 1. should be a float
//      (or whatever X is, not a uchar).
//
//  Programmer: Hank Childs
//  Creation:   November 3, 2003
//
//  Modifications:
//    Brad Whitlock, Wed Apr 18 13:35:09 PDT 2012
//    Return float unless the input is double.
//
// ****************************************************************************

vtkDataArray *
avtConstantCreatorExpression::CreateArray(vtkDataArray *in)
{
    if (in->GetDataType() == VTK_DOUBLE)
        return in->NewInstance();

    return vtkFloatArray::New();
}


