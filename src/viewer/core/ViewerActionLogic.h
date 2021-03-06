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

#ifndef VIEWER_ACTION_LOGIC_H
#define VIEWER_ACTION_LOGIC_H
#include <viewercore_exports.h>
#include <ViewerRPC.h>
#include <ViewerBase.h>

class DataNode;
class ViewerWindow;
class ViewerWindowManager;

// ****************************************************************************
// Class: ViewerActionBase
//
// Purpose:
//   This is an abstract base class for actions that the viewer can perform.
//
// Notes:      
//
// Programmer: Brad Whitlock
// Creation:   Mon Aug 18 15:10:25 PDT 2014
//
// Modifications:
//
// ****************************************************************************

class VIEWERCORE_API ViewerActionLogic : public ViewerBase
{
public:
    ViewerActionLogic(ViewerWindow *win);
    virtual ~ViewerActionLogic();

    ViewerWindow *GetWindow() const;

    virtual void Execute() = 0;
    void PostponeExecute(int activeAction, bool toggled);

    virtual bool CopyFrom(const ViewerActionLogic *);
    virtual bool CreateNode(DataNode *);
    virtual void SetFromNode(DataNode *,const std::string &);

    void         SetRPCType(ViewerRPC::ViewerRPCType);
    ViewerRPC::ViewerRPCType GetRPCType() const;
    std::string  GetName() const;

    static  void SetArgs(const ViewerRPC &a);
    static  const ViewerRPC &GetArgs();

    static void SetPostponeActionCallback(void (*cb)(int, const ViewerRPC &, void *),
                                          void *cbdata);

protected:
    virtual void Setup(int activeAction, bool toggled);

    ViewerWindow               *window;
    ViewerRPC::ViewerRPCType    rpcType;

    static ViewerWindowManager *windowMgr;
    static ViewerRPC            args;

    static void (*PostponeActionCB)(int, const ViewerRPC &, void *);
    static void *PostponeActionCBData;
};

#endif
