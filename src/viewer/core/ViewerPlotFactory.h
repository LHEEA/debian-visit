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
//                             ViewerPlotFactory.h                           //
// ************************************************************************* //

#ifndef VIEWER_PLOT_FACTORY_H
#define VIEWER_PLOT_FACTORY_H
#include <viewercore_exports.h>
#include <ViewerBase.h>
#include <avtSILRestriction.h>
#include <EngineKey.h>

class AttributeSubject;
class ViewerPlot;
class ViewerPlotPluginInfo;


// ****************************************************************************
//  Class: ViewerPlotFactory
//
//  Purpose:
//    ViewerPlotFactory is a factory for creating plots.  It also has
//    methods for manipulating the plot attributes.  When the class is
//    instantiated it registers all the different plot types.
//
//  Programmer: Eric Brugger
//  Creation:   August 23, 2000
//
//  Modifications:
//    Brad Whitlock, Fri Dec 8 17:16:55 PST 2000
//    I modified the CreatePlot method to accept more arguments.
//
//    Eric Brugger, Wed Dec 20 10:25:16 PST 2000
//    I modified the plot factory so that the constructor registers the
//    various plot types, instead of relying on the creator of the factory
//    to do so.  I also added methods for retrieving the default and client
//    attribute subjects for a given plot type.
//
//    Eric Brugger, Thu Mar  8 15:26:36 PST 2001
//    I modified the class to use the plot plugin manager.
//
//    Jeremy Meredith, Thu Jul 26 09:53:57 PDT 2001
//    Renamed plugin info to include the word "plot".
//
//    Jeremy Meredith, Fri Sep 28 13:47:32 PDT 2001
//    Removed the general plugin info since the viewer info is derived
//    from it now.
//
//    Brad Whitlock, Fri Apr 4 10:27:40 PDT 2003
//    I added nStates to the argument list.
//
//    Brad Whitlock, Fri Mar 26 08:34:02 PDT 2004
//    I made it use strings in the constructor and I replaced frame0, frame1
//    with the plotState argument.
//
//    Jeremy Meredith, Thu Mar 25 17:40:30 PST 2004
//    Added support for simulations by adding an engine key to map a plot
//    to the engine used to create it.
//
//    Brad Whitlock, Fri Apr 2 16:05:29 PST 2004
//    I added a couple more arguments to the CreatePlot method.
//
//    Brad Whitlock, Tue Jun 24 14:48:45 PDT 2008
//    Inherit ViewerBase.
//
// ****************************************************************************

class VIEWERCORE_API ViewerPlotFactory : private ViewerBase
{
  public:
    ViewerPlotFactory();
    virtual ~ViewerPlotFactory();

    int GetNPlotTypes() const;

    ViewerPlot *CreatePlot(const int type, const EngineKey &ek,
                           const std::string &hostName,
                           const std::string &databaseName,
                           const std::string &var,
                           avtSILRestriction_p silr,
                           const int plotState,
                           const int nStates,
                           const int cacheIndex,
                           const int nCacheIndices) const;

    AttributeSubject *GetDefaultAtts(const int type) const;
    AttributeSubject *GetClientAtts(const int type) const;

    void SetClientAttsFromDefault(const int type);
    void SetDefaultAttsFromClient(const int type);

  private:
    int                   nTypes;
    ViewerPlotPluginInfo  **viewerPluginInfo;
};

#endif
