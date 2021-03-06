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

#ifndef VIEWER_ACTION_UI_TOGGLE_H
#define VIEWER_ACTION_UI_TOGGLE_H
#include <viewer_exports.h>
#include <ViewerActionUISingle.h>
#include <QPixmap>

// ****************************************************************************
// Class: ViewerActionUIToggle
//
// Purpose:
//   This class represents a viewer action that can be toggled.
//
// Notes:       It provides options for having the toggled icon be different
//              than the regular icon.
//
// Programmer: Brad Whitlock
// Creation:   Mon Feb 3 13:39:20 PST 2003
//
// Modifications:
//   Brad Whitlock, Mon Aug 2 10:10:26 PDT 2004
//   I turned the pixmaps into pointers to get rid a runtime warning about
//   creating pixmaps in -nowin mode.
//
// ****************************************************************************

class VIEWER_API ViewerActionUIToggle : public ViewerActionUISingle
{
public:
    ViewerActionUIToggle(ViewerActionLogic *L);
    virtual ~ViewerActionUIToggle();

    virtual bool Checked() const;
    virtual void Update();

protected:
    virtual void PreExecute();
    virtual void PostponeExecute();

    virtual void SetIcons(const QPixmap &p1, const QPixmap &p2);

    bool     toggled;
    QPixmap *regularIcon;
    QPixmap *toggledIcon;
};

#endif
