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
//  File: TraceHistoryViewerEnginePluginInfo.C
// ************************************************************************* //

#include <TraceHistoryPluginInfo.h>
#include <TraceHistoryAttributes.h>

//
// Storage for static data elements.
//
TraceHistoryAttributes *TraceHistoryViewerEnginePluginInfo::clientAtts = NULL;
TraceHistoryAttributes *TraceHistoryViewerEnginePluginInfo::defaultAtts = NULL;

// ****************************************************************************
//  Method:  TraceHistoryViewerEnginePluginInfo::InitializeGlobalObjects
//
//  Purpose:
//    Initialize the operator atts.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************
void
TraceHistoryViewerEnginePluginInfo::InitializeGlobalObjects()
{
    TraceHistoryViewerEnginePluginInfo::clientAtts  = new TraceHistoryAttributes;
    TraceHistoryViewerEnginePluginInfo::defaultAtts = new TraceHistoryAttributes;
}

// ****************************************************************************
//  Method: TraceHistoryViewerEnginePluginInfo::GetClientAtts
//
//  Purpose:
//    Return a pointer to the viewer client attributes.
//
//  Returns:    A pointer to the viewer client attributes.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

AttributeSubject *
TraceHistoryViewerEnginePluginInfo::GetClientAtts()
{
    return clientAtts;
}

// ****************************************************************************
//  Method: TraceHistoryViewerEnginePluginInfo::GetDefaultAtts
//
//  Purpose:
//    Return a pointer to the viewer default attributes.
//
//  Returns:    A pointer to the viewer default attributes.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

AttributeSubject *
TraceHistoryViewerEnginePluginInfo::GetDefaultAtts()
{
    return defaultAtts;
}

// ****************************************************************************
//  Method: TraceHistoryViewerEnginePluginInfo::SetClientAtts
//
//  Purpose:
//    Set the viewer client attributes.
//
//  Arguments:
//    atts      A pointer to the new client attributes.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

void
TraceHistoryViewerEnginePluginInfo::SetClientAtts(AttributeSubject *atts)
{
    *clientAtts = *(TraceHistoryAttributes *)atts;
    clientAtts->Notify();
}

// ****************************************************************************
//  Method: TraceHistoryViewerEnginePluginInfo::GetClientAtts
//
//  Purpose:
//    Get the viewer client attributes.
//
//  Arguments:
//    atts      A pointer to return the client default attributes in.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

void
TraceHistoryViewerEnginePluginInfo::GetClientAtts(AttributeSubject *atts)
{
    *(TraceHistoryAttributes *)atts = *clientAtts;
}

// ****************************************************************************
//  Method: TraceHistoryViewerEnginePluginInfo::InitializeOperatorAtts
//
//  Purpose:
//    Initialize the operator attributes to the default attributes.
//
//  Arguments:
//    atts        The attribute subject to initialize.
//    plot        The viewer plot that owns the operator.
//    fromDefault True to initialize the attributes from the defaults. False
//                to initialize from the current attributes.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

void
TraceHistoryViewerEnginePluginInfo::InitializeOperatorAtts(AttributeSubject *atts,
                                              const avtPlotMetaData &plot,
                                              const bool fromDefault)
{
    if (fromDefault)
        *(TraceHistoryAttributes*)atts = *defaultAtts;
    else
        *(TraceHistoryAttributes*)atts = *clientAtts;

    UpdateOperatorAtts(atts, plot);
}

// ****************************************************************************
//  Method: TraceHistoryViewerEnginePluginInfo::UpdateOperatorAtts
//
//  Purpose:
//    Update the operator attributes when using operator expressions.
//
//  Arguments:
//    atts        The attribute subject to update.
//    plot        The viewer plot that owns the operator.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

void
TraceHistoryViewerEnginePluginInfo::UpdateOperatorAtts(AttributeSubject *atts, const avtPlotMetaData &plot)
{
}

// ****************************************************************************
//  Method: TraceHistoryViewerEnginePluginInfo::GetMenuName
//
//  Purpose:
//    Return a pointer to the name to use in the viewer menus.
//
//  Returns:    A pointer to the name to use in the viewer menus.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

const char *
TraceHistoryViewerEnginePluginInfo::GetMenuName() const
{
    return "TraceHistory";
}

