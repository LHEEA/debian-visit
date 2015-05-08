/*****************************************************************************
*
* Copyright (c) 2000 - 2015, Lawrence Livermore National Security, LLC
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
//                            avtPICS_TesterFileFormat.h                     //
// ************************************************************************* //

#ifndef AVT_PICS_Tester_FILE_FORMAT_H
#define AVT_PICS_Tester_FILE_FORMAT_H

#include <avtMTMDFileFormat.h>

#include <vector>


// ****************************************************************************
//  Class: avtPICS_TesterFileFormat
//
//  Purpose:
//      Reads in PICS_Tester files as a plugin to VisIt.
//
//  Programmer: hchilds -- generated by xml2avt
//  Creation:   Tue Mar 6 07:45:19 PDT 2012
//
// ****************************************************************************

class avtPICS_TesterFileFormat : public avtMTMDFileFormat
{
  public:
                       avtPICS_TesterFileFormat(const char *);
    virtual           ~avtPICS_TesterFileFormat() {;};

    bool                  HasInvariantMetaData(void) const { return false; };
    bool                  HasInvariantSIL(void) const { return false; };

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    virtual void      *GetAuxiliaryData(const char *var, int timestep, 
                                        int domain, const char *type, void *args, 
                                        DestructorFunction &);

    //
    // If you know the times and cycle numbers, overload this function.
    // Otherwise, VisIt will make up some reasonable ones for you.
    //
    // virtual void        GetCycles(std::vector<int> &);
    virtual void        GetTimes(std::vector<double> &t) { t = times; };
    //

    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "PICS_Tester"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);

  protected:
    // DATA MEMBERS

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);

    void                   ReadHeader(const char *);

    bool                   isRectilinear;
    int                    rank;
    std::vector<int>       numBlocks[3];
    std::vector<int>       numCells[3];
    std::vector<double>    times;
    std::vector<int>       cycles;
    std::vector<double>    vels;
    std::vector<double>    magnitudes;

    enum FlowType { UNKNOWN,
                    STANDARD,
                    DOUBLE_GYRE,
                    ABC_FLOW_STEADY_STATE,
                    ABC_FLOW_APERIODIC };

    FlowType flowType;

    double global_bounds[3];

    // Double gyre flow constants
    double dg_A;
    double dg_epsilon;
    double dg_period;

    // ABC flow constants
    double abc_c0;
    double abc_c1;
    double abc_c2;

    int abc_signalA;
    int abc_signalB;
    int abc_signalC;
};

#endif
