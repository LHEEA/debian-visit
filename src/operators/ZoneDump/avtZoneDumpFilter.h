/*****************************************************************************
*
* Copyright (c) 2000 - 2014, Lawrence Livermore National Security, LLC
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
//  File: avtZoneDumpFilter.h
// ************************************************************************* //

#ifndef AVT_ZoneDump_FILTER_H
#define AVT_ZoneDump_FILTER_H

#include <avtPluginDataTreeIterator.h>

#include <ZoneDumpAttributes.h>

#include <string>
#include <vector>

class vtkDataSet;


// ****************************************************************************
//  Class: avtZoneDumpFilter
//
//  Purpose:
//      A plugin operator for ZoneDump.
//
//  Programmer: harrison37 -- generated by xml2avt
//  Creation:   Tue Mar 13 09:00:34 PDT 2007
//
//  Modifications:
//    Cyrus Harrison, Mon Apr 30 10:51:03 PDT 2007
//    Fixed spelling mistake.
//
//    Eric Brugger, Tue Aug 19 09:53:03 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

class avtZoneDumpFilter : public avtPluginDataTreeIterator
{
  public:
                         avtZoneDumpFilter();
    virtual             ~avtZoneDumpFilter();

    static avtFilter    *Create();

    virtual const char  *GetType(void)  { return "avtZoneDumpFilter"; };
    virtual const char  *GetDescription(void)
                             { return "Zone Dump"; };

    virtual void         SetAtts(const AttributeGroup*);
    virtual bool         Equivalent(const AttributeGroup*);

  protected:

    // ************************************************************************
    //  Class: avtZoneDumpFilter::ZoneInfo
    //
    //  Purpose:
    //      Helper that holds zone info.
    //
    //  Programmer: Cyrus Harrison
    //  Creation:   April 2, 2007
    //
    // ************************************************************************
    class ZoneInfo
    {
      public:
                   ZoneInfo();
                   ZoneInfo(int g, int d, int z,
                            int i, int j, int k,
                            float val);

        virtual   ~ZoneInfo();

        void       Print(ostream &os, const std::string &sep = " ") const;

        void       Pack(unsigned char *);
        void       Unpack(unsigned char *);

        bool       operator==(const ZoneInfo &b);

        static int PackedSize()
                    { return sizeof(int) *6 + sizeof(float); }

        int        groupId;
        int        domainId;
        int        zone;
        int        i, j, k;
        float      value;
    };

    ZoneDumpAttributes   atts;

    virtual avtDataRepresentation *ExecuteData(avtDataRepresentation *);
    virtual avtContract_p ModifyContract
                                 (avtContract_p contract);

    void                  PreExecute();
    void                  PostExecute();

    void                  GetOriginalLogicalIndices(vtkDataSet *ds,
                                                   int zone,
                                                   int ijk[3]);
    void                  SaveOutput(const std::string &, std::vector<ZoneInfo> &);

    std::vector<ZoneInfo>      zones;

};


#endif
