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
//                         avtRandomExpression.h                             //
// ************************************************************************* //

#ifndef AVT_RANDOM_FILTER_H
#define AVT_RANDOM_FILTER_H

#include <avtSingleInputExpressionFilter.h>

class     vtkDataArray;
class     ArgsExpr;
class     ExprPipelineState;

// ****************************************************************************
//  Class: avtRandomExpression
//
//  Purpose:
//      Creates a random number at each point.  Mostly used for odd effects in
//      movie-making.
//          
//  Programmer: Hank Childs
//  Creation:   March 7, 2003
//
//  Modifications:
//
//    Hank Childs, Thu Feb  5 17:11:06 PST 2004
//    Moved inlined constructor and destructor definitions to .C files
//    because certain compilers have problems with them.
//
//    Hank Childs, Mon Jul 10 09:03:13 PDT 2006
//    Added PreExecute.
//
//    Hank Childs, Thu Aug 24 11:24:41 PDT 2006
//    Remove PreExecute, since it was not successfully accomplishing its
//    purpose (setting up the seed for the random number generator in a
//    reproducible way).
//
//    Hank Childs, Wed Aug 22 09:50:06 PDT 2007
//    Declare variable dimension to always be 1.
//
// ****************************************************************************

class EXPRESSION_API avtRandomExpression : public avtSingleInputExpressionFilter
{
  public:
                              avtRandomExpression();
    virtual                  ~avtRandomExpression();

    virtual const char       *GetType(void) { return "avtRandomExpression"; };
    virtual const char       *GetDescription(void)
                                           {return "Assigning random #.";};
    virtual void              ProcessArguments(ArgsExpr*, ExprPipelineState *);
  protected:
    virtual vtkDataArray     *DeriveVariable(vtkDataSet *, int currentDomainsIndex);
    virtual bool              IsPointVariable(void)  { return true; };
    virtual int               GetVariableDimension() { return 1; }
};


#endif


