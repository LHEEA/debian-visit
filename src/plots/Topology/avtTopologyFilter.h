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
//                              avtTopologyFilter.h                          //
// ************************************************************************* //

#ifndef AVT_Topology_FILTER_H
#define AVT_Topology_FILTER_H

#include <avtSIMODataTreeIterator.h>

#include <string>

class vtkCell;
class vtkContourFilter;
class vtkDataArray;
class vtkIdList;


// ****************************************************************************
//  Class: avtTopologyFilter
//
//  Purpose:
//      This operator is the implied operator associated with an Topology plot.
//
//  Programmer: haddox1 -- generated by xml2info
//  Creation:   Thu Jun 26 15:59:09 PST 2003
//
//  Modifications:
//    Eric Brugger, Tue Aug 19 11:41:13 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

class avtTopologyFilter : public avtSIMODataTreeIterator
{
  public:
    static const std::string labelNames[4];
      
                              avtTopologyFilter();
    virtual                  ~avtTopologyFilter();

    virtual const char       *GetType(void)   { return "avtTopologyFilter"; };
    virtual const char       *GetDescription(void)
                                  { return "Finding Topology"; };

    void              SetTolerance(double t)   { tolerance  =  t; }
    void              SetHitpercent(double hp) { hitpercent = hp; }

    virtual void              ReleaseData();

  protected:
    double tolerance;
    double hitpercent;
    
    vtkContourFilter *cf;
    
    virtual avtDataTree_p     ExecuteDataTree(avtDataRepresentation *);
    virtual void              UpdateDataObjectInfo(void);
    
    vtkDataArray             *GetGradient(vtkDataSet *, vtkDataArray *);

    float                     EvaluateComponent(float, float, float, float,
                                                float, float, float, 
                                                vtkDataSet *, vtkDataArray *,
                                                vtkIdList *);    
    
    float                     EvaluateValue(float, float, float, vtkDataSet *,
                                            vtkDataArray *,vtkIdList *,bool &);

    bool                      GetLocalGradient(int, vtkDataSet *,
                                               vtkDataArray *, double[3], int);
};


#endif
