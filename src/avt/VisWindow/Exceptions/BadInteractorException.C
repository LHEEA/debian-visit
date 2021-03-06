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
//                          BadInteractorException.C                         //
// ************************************************************************* //

#include <BadInteractorException.h>


using namespace std;


// ****************************************************************************
//  Method: BadInteractorException constructor
//
//  Programmer: Hank Childs
//  Creation:   May 19, 2000
//
//  Modifications:
//    Kathleen Bonnell, Fri Apr 26 11:17:45 PDT 2002
//    Added LINEOUT.
//
//    Kathleen Bonnell, Fri Jun 27 16:43:23 PDT 2003 
//    Pick renamed ZonePick, added NodePick. 
//
//    Gunther H. Weber, Wed Mar 19 16:10:11 PDT 2008
//    Added SPREADSHEET_PICK 
//
//   Jonathan Byrd (Allinea Software), Sun Dec 18, 2011
//   Added the DDT_PICK mode
//
// ****************************************************************************

BadInteractorException::BadInteractorException(INTERACTION_MODE mode)
{
    string  modeS;
    switch (mode)
    {
      case NAVIGATE:
        modeS = "Navigate";
        break;
      case ZOOM:
        modeS = "Zoom";
        break;
      case ZONE_PICK:
        modeS = "ZonePick";
        break;
      case NODE_PICK:
        modeS = "NodePick";
        break;
      case LINEOUT:
        modeS = "Lineout";
        break;
      case SPREADSHEET_PICK:
        modeS = "SpreadsheetPick";
        break;
      case DDT_PICK:
        modeS = "DDTPick";
        break;
      default:
        modeS = "Unaccounted For Mode";
        break;
    };

    msg = "Could not handle interactor \"" + modeS + "\"";
}


