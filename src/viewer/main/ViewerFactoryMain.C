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
#include <ViewerFactoryMain.h>

#include <ViewerFileServer.h>
#include <ViewerEngineManager.h>

// ****************************************************************************
// Method: ViewerFactoryMain::ViewerFactoryMain
//
// Purpose:
//   Constructor.
//
// Programmer: Brad Whitlock
// Creation:   Fri Aug 22 00:18:38 PDT 2014
//
// Modifications:
//
// ****************************************************************************

ViewerFactoryMain::ViewerFactoryMain() : ViewerFactory()
{
}

// ****************************************************************************
// Method: ViewerFactoryMain::~ViewerFactoryMain
//
// Purpose:
//   Destructor.
//
// Programmer: Brad Whitlock
// Creation:   Fri Aug 22 00:18:38 PDT 2014
//
// Modifications:
//
// ****************************************************************************

ViewerFactoryMain::~ViewerFactoryMain()
{
}

// ****************************************************************************
// Method: ViewerFactoryMain::CreateFileServerInterface
//
// Purpose:
//   Creates the file server interface we'll use.
//
// Returns:    A pointer to the new file server interface.
//
// Programmer: Brad Whitlock
// Creation:   Tue Oct 21 15:02:52 PDT 2014
//
// Modifications:
//
// ****************************************************************************

ViewerFileServerInterface *
ViewerFactoryMain::CreateFileServerInterface()
{
    return new ViewerFileServer;
}

// ****************************************************************************
// Method: ViewerFactoryMain::CreateEngineManagerInterface
//
// Purpose:
//   Creates the engine manager interface we'll use.
//
// Returns:    A pointer to the new engine manager interface.
//
// Programmer: Brad Whitlock
// Creation:   Tue Oct 21 15:02:52 PDT 2014
//
// Modifications:
//
// ****************************************************************************

ViewerEngineManagerInterface *
ViewerFactoryMain::CreateEngineManagerInterface()
{
    return new ViewerEngineManager;
}
