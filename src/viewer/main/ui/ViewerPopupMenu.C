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

#include <ViewerPopupMenu.h>
#include <ViewerActionUI.h>
#include <ViewerProperties.h>
#include <ViewerWindowUI.h>

#include <QMenu>
#include <QButtonGroup>
#include <QCursor>
#include <QRadioButton>
#include <visitstream.h>

// ****************************************************************************
//  Method: ViewerPopupMenu::ViewerPopupMenu
//
//  Purpose: 
//    Constructor for the ViewerPopupMenu class.
//
//  Arguments:
//    win : A pointer to the window that owns this menu.
//
//  Programmer: Brad Whitlock
//  Creation:   Tue Nov 7 12:02:49 PDT 2000
//
//  Modifications:
//    Brad Whitlock, Tue May 27 13:46:56 PDT 2008
//    Qt 4.
//
//    Brad Whitlock, Tue Apr 14 14:21:27 PDT 2009
//    Inherit ViewerBase.
//
// ****************************************************************************

ViewerPopupMenu::ViewerPopupMenu(ViewerWindowUI *win) : ViewerBaseUI(), menus()
{
    //
    // Keep a pointer to the window that created this menu.
    //
    window = win;

    //
    // Create the popup menu widget.
    //
    if(GetViewerProperties()->GetNowin())
        popup = 0;
    else
        popup = new QMenu(0);
}

// ****************************************************************************
//  Method: ViewerPopupMenu::~ViewerPopupMenu
//
//  Purpose: 
//    Destructor for the ViewerPopupMenu class.
//
//  Programmer: Brad Whitlock
//  Creation:   Tue Nov 7 12:04:02 PDT 2000
//
//  Modifications:
//   
// ****************************************************************************

ViewerPopupMenu::~ViewerPopupMenu()
{
}

// ****************************************************************************
//  Method: ViewerPopupMenu::ShowMenu
//
//  Purpose: 
//    Shows the popup menu at the current cursor location.
//
//  Programmer: Brad Whitlock
//  Creation:   Tue Nov 7 12:04:21 PDT 2000
//
//  Modifications:
//   Brad Whitlock, Mon Nov 4 13:12:51 PST 2002
//   I made the menu show manually when it is disabled because otherwise it
//   does not show up.
//
//   Marc Durant, Thu Jan 12 13:50:00 MST 2012
//   When the menu is disabled, do not force it to appear.
//
// ****************************************************************************

void
ViewerPopupMenu::ShowMenu()
{
    if(popup)
    {
        if(popup->isEnabled())
            popup->popup(QCursor::pos());
    }
}

// ****************************************************************************
//  Method: ViewerPopupMenu::HideMenu
//
//  Purpose: 
//    Hides the popup menu.
//
//  Programmer: Brad Whitlock
//  Creation:   Tue Nov 7 12:04:49 PDT 2000
//
//  Modifications:
//   
// ****************************************************************************

void
ViewerPopupMenu::HideMenu()
{
    if(popup)
        popup->hide();
}

// ****************************************************************************
// Method: ViewerPopupMenu::SetEnabled
//
// Purpose: 
//   Sets the enabled state of the viewer popup menu.
//
// Arguments:
//   val : The new enabled state.
//
// Programmer: Brad Whitlock
// Creation:   Wed Oct 30 15:25:03 PST 2002
//
// Modifications:
//   
// ****************************************************************************

void
ViewerPopupMenu::SetEnabled(bool val)
{
    if(popup)
        popup->setEnabled(val);
}

// ****************************************************************************
// Method: ViewerPopupMenu::IsEnabled
//
// Purpose: 
//   Gets the enabled state of the viewer popup menu.
//
// Arguments:
//
// Programmer: Marc Durant
// Creation:   Tue Dec 27 13:54:00 MDT 2011
//
// Modifications:
//   
// ****************************************************************************

bool
ViewerPopupMenu::IsEnabled()
{
  if (popup)
      return popup->isEnabled();
  return false;
}

// ****************************************************************************
// Method: ViewerPopupMenu::AddAction
//
// Purpose: 
//   Lets the action add its own entry into the menu.
//
// Arguments:
//   action : The action that wants to be added to the menu.
//
// Programmer: Brad Whitlock
// Creation:   Wed Jan 29 14:44:18 PST 2003
//
// Modifications:
//   
// ****************************************************************************

void
ViewerPopupMenu::AddAction(ViewerActionUI *action)
{
    if(popup != NULL && action != NULL)
        action->ConstructMenu(popup);
}

// ****************************************************************************
// Method: ViewerPopupMenu::AddAction
//
// Purpose: 
//   Lets the action add its own entry into the menu.
//
// Arguments:
//   menuName : The name of the menu to which the action will be added.
//   action   : The action that wants to be added to the menu.
//
// Programmer: Brad Whitlock
// Creation:   Wed Jan 29 14:44:18 PST 2003
//
// Modifications:
//   
// ****************************************************************************

void
ViewerPopupMenu::AddAction(const std::string &menuName, ViewerActionUI *action)
{
    if(popup != NULL && action != NULL)
    {
        QMenu *menu = CreateMenu(menuName);
        if(menu)
            action->ConstructMenu(menu);
    }
}

// ****************************************************************************
// Method: ViewerPopupMenu::RemoveAction
//
// Purpose: 
//   Lets the action remove itself from all of the menus.
//
// Arguments:
//   action : The action to remove from the menus.
//
// Programmer: Brad Whitlock
// Creation:   Tue Feb 25 10:14:25 PDT 2003
//
// Modifications:
//   
// ****************************************************************************

void
ViewerPopupMenu::RemoveAction(ViewerActionUI *action)
{
    if(popup)
    {
        action->RemoveFromMenu(popup);
        MenuMap::iterator pos;
        for(pos = menus.begin(); pos != menus.end(); ++pos)
            action->RemoveFromMenu(pos->second.menu);
    }
}

// ****************************************************************************
// Method: ViewerPopupMenu::EnableMenu
//
// Purpose: 
//   Enables a submenu.
//
// Arguments:
//   menuName : The name of the menu to Enable.
//
// Programmer: Brad Whitlock
// Creation:   Fri Jan 31 14:13:25 PST 2003
//
// Modifications:
//   Brad Whitlock, Tue May 27 14:08:06 PDT 2008
//   Qt 4.
//
// ****************************************************************************

void
ViewerPopupMenu::EnableMenu(const std::string &menuName)
{
    if(popup)
    {
        MenuMap::iterator pos = menus.find(menuName);
        if(pos != menus.end())
            pos->second.action->setEnabled(true);
    }
}

// ****************************************************************************
// Method: ViewerPopupMenu::DisableMenu
//
// Purpose: 
//   Disables a submenu.
//
// Arguments:
//   menuName : The name of the menu to disable.
//
// Programmer: Brad Whitlock
// Creation:   Fri Jan 31 14:13:25 PST 2003
//
// Modifications:
//   Brad Whitlock, Tue May 27 14:08:06 PDT 2008
//   Qt 4.
//   
// ****************************************************************************

void
ViewerPopupMenu::DisableMenu(const std::string &menuName)
{
    if(popup)
    {
        MenuMap::iterator pos = menus.find(menuName);
        if(pos != menus.end())
            pos->second.action->setEnabled(false);
    }
}

// ****************************************************************************
// Method: ViewerPopupMenu::CreateMenu
//
// Purpose: 
//   Creates a menu with the given name.
//
// Arguments:
//   menuName : The name of the menu to create.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jan 30 10:56:12 PDT 2003
//
// Modifications:
//   
// ****************************************************************************

QMenu *
ViewerPopupMenu::CreateMenu(const std::string &menuName)
{
    if(popup)
    {
        MenuMap::iterator pos;
        if((pos = menus.find(menuName)) != menus.end())
            return pos->second.menu;
        else
        {
            // Create a new popup menu and store it in the map.
            QMenu *menu = new QMenu(menuName.c_str(), popup);

            // Insert the new popup menu into the parent popup menu.
            QAction *action = popup->addMenu(menu);

            // Store the menu pointer and id for later.
            menus[menuName] = SubMenuInfo(menu, action);

            return menu;
        }
    }

    return 0;
}

//
// ViewerPopupMenu::SubMenuInfo class
//

ViewerPopupMenu::SubMenuInfo::SubMenuInfo()
{
    menu = 0;
    action = 0;
}

ViewerPopupMenu::SubMenuInfo::SubMenuInfo(const ViewerPopupMenu::SubMenuInfo &obj)
{
    menu = obj.menu;
    action = obj.action;
}

ViewerPopupMenu::SubMenuInfo::SubMenuInfo(QMenu *m, QAction *a)
{
    menu = m;
    action = a;
}

ViewerPopupMenu::SubMenuInfo::~SubMenuInfo()
{
}

void
ViewerPopupMenu::SubMenuInfo::operator =(const ViewerPopupMenu::SubMenuInfo &obj)
{
    menu = obj.menu;
    action = obj.action;
}
