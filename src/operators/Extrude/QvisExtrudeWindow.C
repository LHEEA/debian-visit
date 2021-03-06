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

#include "QvisExtrudeWindow.h"

#include <ExtrudeAttributes.h>

#include <QCheckBox>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>


// ****************************************************************************
// Method: QvisExtrudeWindow::QvisExtrudeWindow
//
// Purpose: 
//   Constructor
//
// Note:       Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

QvisExtrudeWindow::QvisExtrudeWindow(const int type,
                         ExtrudeAttributes *subj,
                         const QString &caption,
                         const QString &shortName,
                         QvisNotepadArea *notepad)
    : QvisOperatorWindow(type,subj, caption, shortName, notepad)
{
    atts = subj;
}


// ****************************************************************************
// Method: QvisExtrudeWindow::~QvisExtrudeWindow
//
// Purpose: 
//   Destructor
//
// Note:       Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

QvisExtrudeWindow::~QvisExtrudeWindow()
{
}


// ****************************************************************************
// Method: QvisExtrudeWindow::CreateWindowContents
//
// Purpose: 
//   Creates the widgets for the window.
//
// Note:       Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void
QvisExtrudeWindow::CreateWindowContents()
{
    QGridLayout *mainLayout = new QGridLayout(0);
    topLayout->addLayout(mainLayout);

    axisLabel = new QLabel(tr("Extrusion axis"), central);
    mainLayout->addWidget(axisLabel,0,0);
    axis = new QLineEdit(central);
    connect(axis, SIGNAL(returnPressed()),
            this, SLOT(axisProcessText()));
    mainLayout->addWidget(axis, 0,1);

    lengthLabel = new QLabel(tr("Length"), central);
    mainLayout->addWidget(lengthLabel,1,0);
    length = new QLineEdit(central);
    connect(length, SIGNAL(returnPressed()),
            this, SLOT(lengthProcessText()));
    mainLayout->addWidget(length, 1,1);

    stepsLabel = new QLabel(tr("Number of steps"), central);
    mainLayout->addWidget(stepsLabel,2,0);
    steps = new QLineEdit(central);
    connect(steps, SIGNAL(returnPressed()),
            this, SLOT(stepsProcessText()));
    mainLayout->addWidget(steps, 2,1);

    preserveOriginalCellNumbers = new QCheckBox(tr("Preserve original cell numbers"), central);
    connect(preserveOriginalCellNumbers, SIGNAL(toggled(bool)),
            this, SLOT(preserveOriginalCellNumbersChanged(bool)));
    mainLayout->addWidget(preserveOriginalCellNumbers, 3,0);

}


// ****************************************************************************
// Method: QvisExtrudeWindow::UpdateWindow
//
// Purpose: 
//   Updates the widgets in the window when the subject changes.
//
// Note:       Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void
QvisExtrudeWindow::UpdateWindow(bool doAll)
{

    for(int i = 0; i < atts->NumAttributes(); ++i)
    {
        if(!doAll)
        {
            if(!atts->IsSelected(i))
            {
                continue;
            }
        }

        switch(i)
        {
          case ExtrudeAttributes::ID_axis:
            axis->setText(DoublesToQString(atts->GetAxis(), 3));
            break;
          case ExtrudeAttributes::ID_length:
            length->setText(DoubleToQString(atts->GetLength()));
            break;
          case ExtrudeAttributes::ID_steps:
            steps->setText(IntToQString(atts->GetSteps()));
            break;
          case ExtrudeAttributes::ID_preserveOriginalCellNumbers:
            preserveOriginalCellNumbers->blockSignals(true);
            preserveOriginalCellNumbers->setChecked(atts->GetPreserveOriginalCellNumbers());
            preserveOriginalCellNumbers->blockSignals(false);
            break;
        }
    }
}


// ****************************************************************************
// Method: QvisExtrudeWindow::GetCurrentValues
//
// Purpose: 
//   Gets values from certain widgets and stores them in the subject.
//
// Note:       Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void
QvisExtrudeWindow::GetCurrentValues(int which_widget)
{
    bool doAll = (which_widget == -1);

    // Do axis
    if(which_widget == ExtrudeAttributes::ID_axis || doAll)
    {
        double val[3];
        if(LineEditGetDoubles(axis, val, 3))
            atts->SetAxis(val);
        else
        {
            ResettingError(tr("Extrusion axis"),
                DoublesToQString(atts->GetAxis(),3));
            atts->SetAxis(atts->GetAxis());
        }
    }

    // Do length
    if(which_widget == ExtrudeAttributes::ID_length || doAll)
    {
        double val;
        if(LineEditGetDouble(length, val))
            atts->SetLength(val);
        else
        {
            ResettingError(tr("Length"),
                DoubleToQString(atts->GetLength()));
            atts->SetLength(atts->GetLength());
        }
    }

    // Do steps
    if(which_widget == ExtrudeAttributes::ID_steps || doAll)
    {
        int val;
        if(LineEditGetInt(steps, val))
            atts->SetSteps(val);
        else
        {
            ResettingError(tr("Number of steps"),
                IntToQString(atts->GetSteps()));
            atts->SetSteps(atts->GetSteps());
        }
    }

}


//
// Qt Slot functions
//


void
QvisExtrudeWindow::axisProcessText()
{
    GetCurrentValues(ExtrudeAttributes::ID_axis);
    Apply();
}


void
QvisExtrudeWindow::lengthProcessText()
{
    GetCurrentValues(ExtrudeAttributes::ID_length);
    Apply();
}


void
QvisExtrudeWindow::stepsProcessText()
{
    GetCurrentValues(ExtrudeAttributes::ID_steps);
    Apply();
}


void
QvisExtrudeWindow::preserveOriginalCellNumbersChanged(bool val)
{
    atts->SetPreserveOriginalCellNumbers(val);
    SetUpdate(false);
    Apply();
}


