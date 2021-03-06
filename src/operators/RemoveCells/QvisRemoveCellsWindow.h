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

#ifndef QVISREMOVECELLSWINDOW_H
#define QVISREMOVECELLSWINDOW_H

#include <QvisOperatorWindow.h>
#include <AttributeSubject.h>

class RemoveCellsAttributes;
class QLineEdit;
class QListWidget;

// ****************************************************************************
// Class: QvisRemoveCellsWindow
//
// Purpose: 
//   Defines QvisRemoveCellsWindow class.
//
// Notes:      This class was automatically generated!

// Programmer: xml2window
// Creation:   Thu Jul 17 15:33:35 PST 2003
//
// Modifications:
//   Cyrus Harrison, Thu Aug 21 16:11:16 PDT 2008
//   Qt4 Port.
//
// ****************************************************************************

class QvisRemoveCellsWindow : public QvisOperatorWindow
{
    Q_OBJECT
  public:
    QvisRemoveCellsWindow(const int type,
                         RemoveCellsAttributes *subj,
                         const QString &caption = QString::null,
                         const QString &shortName = QString::null,
                         QvisNotepadArea *notepad = 0);
    virtual ~QvisRemoveCellsWindow();
    virtual void CreateWindowContents();
  protected:
    void UpdateWindow(bool doAll);
    virtual void GetCurrentValues(int which_widget);
  private slots:
    void cellProcessText();
    void domainProcessText();
    void addButtonClicked();
    void removeButtonClicked();
    void changeButtonClicked();
    void selectionChanged(int);
  private:
    void    ParseEntryString(const QString &str,int &cell, int &domain);
    QString CreateEntryString(int cell, int domain);
    void    GetCurrentCell(int &cell,int &domain);
        
    QLineEdit *cell;
    QLineEdit *domain;

    QListWidget  *cellList;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *changeButton;

    RemoveCellsAttributes *atts;
};



#endif
