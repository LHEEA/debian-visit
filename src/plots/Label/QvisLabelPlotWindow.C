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

#include <QvisLabelPlotWindow.h>

#include <LabelAttributes.h>
#include <ViewerProxy.h>
#include <StringHelpers.h>

#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QvisColorButton.h>
#include <snprintf.h>


// ****************************************************************************
// Method: QvisLabelPlotWindow::QvisLabelPlotWindow
//
// Purpose: 
//   Constructor for the QvisLabelPlotWindow class.
//
// Arguments:
//   type      : An identifier used to identify the plot type in the viewer.
//   subj      : The label attributes that the window observes.
//   caption   : The caption displayed in the window decorations.
//   shortName : The name used in the notepad.
//   notepad   : The notepad area where the window posts itself.
//
// Programmer: Brad Whitlock
// Creation:   Thu Oct 21 18:18:16 PST 2004
//
// Modifications:
//   Brad Whitlock, Tue Aug 9 14:05:35 PST 2005
//   Added depthTestButtonGroup.
//
// ****************************************************************************

QvisLabelPlotWindow::QvisLabelPlotWindow(const int type,
    LabelAttributes *subj, const QString &caption, const QString &shortName,
    QvisNotepadArea *notepad) : QvisPostableWindowObserver(subj, caption,
        shortName, notepad)
{
    plotType = type;
    labelAtts = subj;

    depthTestButtonGroup = 0;
}

// ****************************************************************************
// Method: QvisLabelPlotWindow::~QvisLabelPlotWindow
//
// Purpose: 
//   Destructor
//
// Programmer: Brad Whitlock
// Creation:   Thu Oct 21 18:18:16 PST 2004
//
// Modifications:
//   Brad Whitlock, Tue Aug 9 14:05:27 PST 2005
//   Added depthTestButtonGroup.
//
//   Cyrus Harrison, Wed Aug 27 08:54:49 PDT 2008
//   Set parent for depthTestButtonGroup, we can avoid explicit delete. 
//
// ****************************************************************************

QvisLabelPlotWindow::~QvisLabelPlotWindow()
{
}

// ****************************************************************************
// Method: QvisLabelPlotWindow::CreateWindowContents
//
// Purpose: 
//   Creates the widgets for the window.
//
// Programmer: Brad Whitlock
// Creation:   Thu Oct 21 18:18:16 PST 2004
//
// Modifications:
//   Brad Whitlock, Tue Aug 2 14:50:32 PST 2005
//   I removed the single cell/node controls. I also added controls for
//   zbuffering and additional controls for changing label color and height
//   for meshes.
//
//   Dave Bremer, Wed Sep 19 19:39:40 PDT 2007
//   I added a line for specifying a printf-style template.
//
//   Brad Whitlock, Tue Apr 22 16:54:16 PDT 2008
//   Added tr()'s
//
//   Cyrus Harrison, Fri Jul 18 14:44:51 PDT 2008
//   Initial Qt4 Port. 
//
//   Allen Sanderson, Sun Mar  7 12:49:56 PST 2010
//   Change layout of window for 2.0 interface changes.
//
//   Hank Childs, Wed Oct 20 11:04:12 PDT 2010
//   Change text heights from spin box to "double spin box".
//
//   Kathleen Biagas, Wed Jun  8 17:10:30 PDT 2016
//   Set keyboard tracking to false for spin boxes so that 'valueChanged'
//   signal will only emit when 'enter' is pressed or spinbox loses focus.
//
// ****************************************************************************

void
QvisLabelPlotWindow::CreateWindowContents()
{
    //
    // Create label selection-related widgets.
    //
    selectionGroupBox = new QGroupBox(central);
    selectionGroupBox->setTitle(tr("Selection"));
    topLayout->addWidget(selectionGroupBox);
    QVBoxLayout *selTopLayout = new QVBoxLayout(selectionGroupBox);

    QGridLayout *selLayout = new QGridLayout();
    selTopLayout->addLayout(selLayout);

    showNodesToggle = new QCheckBox(tr("Show nodes"), selectionGroupBox);
    connect(showNodesToggle, SIGNAL(toggled(bool)),
            this, SLOT(showNodesToggled(bool)));
    selLayout->addWidget(showNodesToggle, 0,0);

    showCellsToggle = new QCheckBox(tr("Show cells"), selectionGroupBox);
    connect(showCellsToggle, SIGNAL(toggled(bool)),
            this, SLOT(showCellsToggled(bool)));
    selLayout->addWidget(showCellsToggle, 0,1);

    restrictNumberOfLabelsToggle = new QCheckBox(tr("Restrict number of labels to"));
    connect(restrictNumberOfLabelsToggle, SIGNAL(toggled(bool)),
            this, SLOT(restrictNumberOfLabelsToggled(bool)));
    selLayout->addWidget(restrictNumberOfLabelsToggle, 1,0,1,2);

    numberOfLabelsSpinBox = new QSpinBox(selectionGroupBox);
    numberOfLabelsSpinBox->setKeyboardTracking(false);
    numberOfLabelsSpinBox->setRange(1, 200000);
    numberOfLabelsSpinBox->setSingleStep(200);
    connect(numberOfLabelsSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(numberOfLabelsChanged(int)));
    selLayout->addWidget(numberOfLabelsSpinBox, 1, 2);

    drawLabelsFacingComboBox = new QComboBox(selectionGroupBox);
    drawLabelsFacingComboBox->addItem(tr("Front"));
    drawLabelsFacingComboBox->addItem(tr("Back"));
    drawLabelsFacingComboBox->addItem(tr("Front or Back"));
    connect(drawLabelsFacingComboBox, SIGNAL(activated(int)),
            this, SLOT(drawLabelsFacingChanged(int)));
    selLayout->addWidget(drawLabelsFacingComboBox, 2, 2);
    selLayout->addWidget(new QLabel(tr("Draw labels that face"),selectionGroupBox)
                         , 2, 0, 1, 2);

    depthTestButtonGroup = new QButtonGroup(selectionGroupBox);
    
    QHBoxLayout *dtLayout = new QHBoxLayout();
    
    QRadioButton *rb = new QRadioButton(tr("Auto"), selectionGroupBox);
    depthTestButtonGroup->addButton(rb, 0);
    dtLayout->addWidget(rb);
    
    rb = new QRadioButton(tr("Always"), selectionGroupBox);
    depthTestButtonGroup->addButton(rb, 1);
    dtLayout->addWidget(rb);
    
    rb = new QRadioButton(tr("Never"), selectionGroupBox);
    depthTestButtonGroup->addButton(rb, 2);
    dtLayout->addWidget(rb);
    
    connect(depthTestButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(depthTestButtonGroupChanged(int)));
    selLayout->addWidget(new QLabel(tr("Depth test mode"), selectionGroupBox), 3, 0);
    selLayout->addLayout(dtLayout, 3, 1, 1, 2);

    //
    // Create formatting widgets
    //
    formattingGroupBox = new QGroupBox(central);
    formattingGroupBox->setTitle(tr("Formatting"));
    topLayout->addWidget(formattingGroupBox);
    QVBoxLayout *fmtTopLayout = new QVBoxLayout(formattingGroupBox);
    QGridLayout *fmtLayout = new QGridLayout();
    fmtTopLayout->addLayout(fmtLayout);

    labelDisplayFormatComboBox = new QComboBox(formattingGroupBox);
    labelDisplayFormatComboBox->addItem(tr("Natural"));
    labelDisplayFormatComboBox->addItem(tr("Logical index"));
    labelDisplayFormatComboBox->addItem(tr("Index"));
    connect(labelDisplayFormatComboBox, SIGNAL(activated(int)),
            this, SLOT(labelDisplayFormatChanged(int)));
    fmtLayout->addWidget(labelDisplayFormatComboBox, 0, 1);
    fmtLayout->addWidget(new QLabel(tr("Label display format"), 
                                    formattingGroupBox), 0, 0);


    specifyTextColor1Toggle = new QCheckBox(tr("Specify label color"),
                                            formattingGroupBox);
    connect(specifyTextColor1Toggle, SIGNAL(toggled(bool)),
            this, SLOT(specifyTextColor1Toggled(bool)));
    fmtLayout->addWidget(specifyTextColor1Toggle, 1, 0);

    textColor1Button = new QvisColorButton(formattingGroupBox);
    connect(textColor1Button, SIGNAL(selectedColor(const QColor&)),
            this, SLOT(textColor1Changed(const QColor&)));
    fmtLayout->addWidget(textColor1Button, 1, 1, Qt::AlignLeft);

    specifyTextColor2Toggle = new QCheckBox(tr("Specify node label color"),
                                            formattingGroupBox);
    connect(specifyTextColor2Toggle, SIGNAL(toggled(bool)),
            this, SLOT(specifyTextColor2Toggled(bool)));
    fmtLayout->addWidget(specifyTextColor2Toggle, 2, 0);

    textColor2Button = new QvisColorButton(formattingGroupBox);
    connect(textColor2Button, SIGNAL(selectedColor(const QColor&)),
            this, SLOT(textColor2Changed(const QColor&)));
    fmtLayout->addWidget(textColor2Button, 2, 1, Qt::AlignLeft);

    textHeight1SpinBox = new QDoubleSpinBox(formattingGroupBox);
    textHeight1SpinBox->setKeyboardTracking(false);
    textHeight1SpinBox->setMinimum(0.0);
    textHeight1SpinBox->setMaximum(100.0);
    textHeight1SpinBox->setSingleStep(0.1);
    textHeight1SpinBox->setSuffix("%");
    connect(textHeight1SpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(textHeight1Changed(double)));
    textHeight1Label = new QLabel(tr("Label height"),formattingGroupBox);
    fmtLayout->addWidget(textHeight1Label, 3, 0);
    fmtLayout->addWidget(textHeight1SpinBox, 3, 1);

    textHeight2SpinBox = new QDoubleSpinBox(formattingGroupBox);
    textHeight2SpinBox->setKeyboardTracking(false);
    textHeight2SpinBox->setMinimum(0.0);
    textHeight2SpinBox->setMaximum(100.0);
    textHeight2SpinBox->setSingleStep(0.1);
    textHeight2SpinBox->setSuffix("%");
    connect(textHeight2SpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(textHeight2Changed(double)));
    textHeight2Label = new QLabel(tr("Node label height"),formattingGroupBox);
    fmtLayout->addWidget(textHeight2Label, 4, 0);
    fmtLayout->addWidget(textHeight2SpinBox, 4, 1);

    horizontalJustificationComboBox = new QComboBox(formattingGroupBox);
    horizontalJustificationComboBox->addItem(tr("Center"));
    horizontalJustificationComboBox->addItem(tr("Left"));
    horizontalJustificationComboBox->addItem(tr("Right"));
    connect(horizontalJustificationComboBox, SIGNAL(activated(int)),
            this, SLOT(horizontalJustificationChanged(int)));
    fmtLayout->addWidget(horizontalJustificationComboBox, 5, 1);
    fmtLayout->addWidget(new QLabel(tr("Horizontal justification"), 
                                    formattingGroupBox), 5, 0);

    verticalJustificationComboBox = new QComboBox(formattingGroupBox);
    verticalJustificationComboBox->addItem(tr("Center"));
    verticalJustificationComboBox->addItem(tr("Top"));
    verticalJustificationComboBox->addItem(tr("Bottom"));
    connect(verticalJustificationComboBox, SIGNAL(activated(int)),
            this, SLOT(verticalJustificationChanged(int)));
    fmtLayout->addWidget(verticalJustificationComboBox, 6, 1);
    fmtLayout->addWidget(new QLabel(tr("Vertical justification"), 
                                    formattingGroupBox), 6, 0);

    
    formatTemplate = new QLineEdit(QString(labelAtts->GetFormatTemplate().c_str()), 
                                   formattingGroupBox);
    connect(formatTemplate, SIGNAL(returnPressed()), 
            this, SLOT(formatTemplateChanged()));

    fmtLayout->addWidget(formatTemplate, 7, 1);
    fmtLayout->addWidget(new QLabel(tr("Format template"), formattingGroupBox), 7, 0);

    //
    // Create the misc stuff
    //
    QGroupBox * miscGroup = new QGroupBox(central);
    miscGroup->setTitle(tr("Misc"));
    topLayout->addWidget(miscGroup);

    QGridLayout *miscLayout = new QGridLayout(miscGroup);
    miscLayout->setMargin(5);
    miscLayout->setSpacing(10);
 
    // Create the legend toggle
    legendToggle = new QCheckBox(tr("Legend"), central);
    connect(legendToggle, SIGNAL(toggled(bool)),
            this, SLOT(legendToggled(bool)));
    miscLayout->addWidget(legendToggle, 0, 0);
}


// ****************************************************************************
// Method: QvisLabelPlotWindow::UpdateWindow
//
// Purpose: 
//   Updates the widgets in the window when the subject changes.
//
// Programmer: Brad Whitlock
// Creation:   Thu Oct 21 18:18:16 PST 2004
//
// Modifications:
//   Brad Whitlock, Tue Aug 2 14:51:19 PST 2005
//   Changed field ordering. Added widgets that allow for setting colors for
//   node and cell labels.
//
//   Dave Bremer, Wed Sep 19 19:39:40 PDT 2007
//   I added a code for updating a printf-style template.
//
//   Brad Whitlock, Tue Apr 22 16:56:14 PDT 2008
//   Added tr()'s
//
//   Cyrus Harrison, Fri Jul 18 14:44:51 PDT 2008
//   Initial Qt4 Port. 
//
//   Hank Childs, Wed Oct 20 11:04:12 PDT 2010
//   Change text heights from spin box to "double spin box".
//
// ****************************************************************************

void
QvisLabelPlotWindow::UpdateWindow(bool doAll)
{
    QString temp;
    QColor  tempcolor;

    for(int i = 0; i < labelAtts->NumAttributes(); ++i)
    {
        if(!doAll)
        {
            if(!labelAtts->IsSelected(i))
            {
                continue;
            }
        }

        switch(i)
        {
        case LabelAttributes::ID_varType:
            {// new scope
            bool varIsMesh = labelAtts->GetVarType() == LabelAttributes::LABEL_VT_MESH;
            showNodesToggle->setEnabled(varIsMesh);
            showCellsToggle->setEnabled(varIsMesh);
            specifyTextColor1Toggle->setText(varIsMesh?tr("Specify cell label color"):tr("Specify label color"));  
            textHeight1Label->setText(varIsMesh?tr("Cell label height") : tr("Label height"));
            if(varIsMesh)
            {
                textColor2Button->show();
                specifyTextColor2Toggle->show();
                textHeight2Label->show();
                textHeight2SpinBox->show();
                updateGeometry();
            }
            else
            {
                textColor2Button->hide();
                specifyTextColor2Toggle->hide();
                textHeight2Label->hide();
                textHeight2SpinBox->hide();
                updateGeometry();
            }
            }
            break;
        case LabelAttributes::ID_legendFlag:
            legendToggle->blockSignals(true);
            legendToggle->setChecked(labelAtts->GetLegendFlag());
            legendToggle->blockSignals(false);
            break;
        case LabelAttributes::ID_showNodes:
            showNodesToggle->blockSignals(true);
            showNodesToggle->setChecked(labelAtts->GetShowNodes());
            showNodesToggle->blockSignals(false);
            break;
        case LabelAttributes::ID_showCells:
            showCellsToggle->blockSignals(true);
            showCellsToggle->setChecked(labelAtts->GetShowCells());
            showCellsToggle->blockSignals(false);
            break;
        case LabelAttributes::ID_restrictNumberOfLabels:
            restrictNumberOfLabelsToggle->blockSignals(true);
            restrictNumberOfLabelsToggle->setChecked(labelAtts->GetRestrictNumberOfLabels());
            restrictNumberOfLabelsToggle->blockSignals(false);
            numberOfLabelsSpinBox->setEnabled(labelAtts->GetRestrictNumberOfLabels());
            break;
        case LabelAttributes::ID_drawLabelsFacing:
            drawLabelsFacingComboBox->blockSignals(true);
            drawLabelsFacingComboBox->setCurrentIndex(int(labelAtts->GetDrawLabelsFacing()));
            drawLabelsFacingComboBox->blockSignals(false);
            break;
        case LabelAttributes::ID_labelDisplayFormat:
            labelDisplayFormatComboBox->blockSignals(true);
            labelDisplayFormatComboBox->setCurrentIndex(int(labelAtts->GetLabelDisplayFormat()));
            labelDisplayFormatComboBox->blockSignals(false);
            break;
        case LabelAttributes::ID_numberOfLabels:
            numberOfLabelsSpinBox->blockSignals(true);
            numberOfLabelsSpinBox->setValue(labelAtts->GetNumberOfLabels());
            numberOfLabelsSpinBox->blockSignals(false);
            break;
        case LabelAttributes::ID_specifyTextColor1:
            specifyTextColor1Toggle->blockSignals(true);
            specifyTextColor1Toggle->setChecked(labelAtts->GetSpecifyTextColor1());
            specifyTextColor1Toggle->blockSignals(false);

            textColor1Button->setEnabled(labelAtts->GetSpecifyTextColor1());
            break;
        case LabelAttributes::ID_textColor1:
            tempcolor = QColor(labelAtts->GetTextColor1().Red(),
                               labelAtts->GetTextColor1().Green(),
                               labelAtts->GetTextColor1().Blue());
            textColor1Button->setButtonColor(tempcolor);
            break;
        case LabelAttributes::ID_textHeight1:
            textHeight1SpinBox->blockSignals(true);
            textHeight1SpinBox->setValue(labelAtts->GetTextHeight1() * 100.f);
            textHeight1SpinBox->blockSignals(false);
            break;

        case LabelAttributes::ID_specifyTextColor2:
            specifyTextColor2Toggle->blockSignals(true);
            specifyTextColor2Toggle->setChecked(labelAtts->GetSpecifyTextColor2());
            specifyTextColor2Toggle->blockSignals(false);

            textColor2Button->setEnabled(labelAtts->GetSpecifyTextColor2());
            break;
        case LabelAttributes::ID_textColor2:
            tempcolor = QColor(labelAtts->GetTextColor2().Red(),
                               labelAtts->GetTextColor2().Green(),
                               labelAtts->GetTextColor2().Blue());
            textColor2Button->setButtonColor(tempcolor);
            break;
        case LabelAttributes::ID_textHeight2:
            textHeight2SpinBox->blockSignals(true);
            textHeight2SpinBox->setValue(labelAtts->GetTextHeight2() * 100.f);
            textHeight2SpinBox->blockSignals(false);
            break;
        case LabelAttributes::ID_horizontalJustification:
            horizontalJustificationComboBox->blockSignals(true);
            horizontalJustificationComboBox->setCurrentIndex(int(labelAtts->
                GetHorizontalJustification()));
            horizontalJustificationComboBox->blockSignals(false);
            break;
        case LabelAttributes::ID_verticalJustification:
            verticalJustificationComboBox->blockSignals(true);
            verticalJustificationComboBox->setCurrentIndex(int(labelAtts->
                GetVerticalJustification()));
            verticalJustificationComboBox->blockSignals(false);
            break;
        case LabelAttributes::ID_depthTestMode:
            depthTestButtonGroup->blockSignals(true);
            depthTestButtonGroup->button(int(labelAtts->GetDepthTestMode()))->setChecked(true);
            depthTestButtonGroup->blockSignals(false);
            break;
        case LabelAttributes::ID_formatTemplate:
            formatTemplate->blockSignals(true);
            formatTemplate->setText(QString(labelAtts->GetFormatTemplate().c_str()));
            formatTemplate->blockSignals(false);
            break;
        }
    }
}


// ****************************************************************************
// Method: QvisLabelPlotWindow::GetCurrentValues
//
// Purpose: 
//   Gets values from certain widgets and stores them in the subject.
//
// Programmer: Brad Whitlock
// Creation:   Thu Oct 21 18:18:16 PST 2004
//
// Modifications:
//   Brad Whitlock, Mon Nov 29 15:27:08 PST 2004
//   Added code to get the values from the numberOfLabelsSpinBox and
//   textHeightSpinBox so it is not necessary to hit the Enter key.
//
//   Brad Whitlock, Tue Aug 2 14:54:10 PST 2005
//   I removed some fields and added code for textHeight2SpinBox.
//
//   Brad Whitlock, Tue Apr 22 16:58:45 PDT 2008
//   Support for internationalization.
//
//   Cyrus Harrison, Fri Jul 18 14:44:51 PDT 2008
//   Initial Qt4 Port. 
//
//   Eric Brugger, Tue Aug 24 10:42:22 PDT 2010
//   I added code for formatTemplate. 
//
//   Hank Childs, Wed Oct 20 11:04:12 PDT 2010
//   Change text heights from spin box to "double spin box".
//
// ****************************************************************************

void
QvisLabelPlotWindow::GetCurrentValues(int which_widget)
{
    bool okay, doAll = (which_widget == -1);
    QString msg, temp;

    // Do numberOfLabels
    if(which_widget == LabelAttributes::ID_numberOfLabels || doAll)
    {
        temp = numberOfLabelsSpinBox->text().trimmed();
        okay = !temp.isEmpty();
        if(okay)
        {
            int val = temp.toInt(&okay);
            if(okay)
                labelAtts->SetNumberOfLabels(val);
        }

        if(!okay)
        {
            ResettingError(tr("number of labels"),
                IntToQString(labelAtts->GetNumberOfLabels()));
            labelAtts->SetNumberOfLabels(labelAtts->GetNumberOfLabels());
        }
    }

    // Do textHeight1
    if(which_widget == LabelAttributes::ID_textHeight1  || doAll)
    {
        temp = textHeight1SpinBox->text();
        int plen = (temp.indexOf(textHeight1SpinBox->prefix()) != -1) ? 
            textHeight1SpinBox->prefix().length() : 0;
        int slen = (temp.indexOf(textHeight1SpinBox->suffix()) != -1) ? 
            textHeight1SpinBox->suffix().length() : 0;
        temp = temp.mid(plen, temp.length() - plen - slen).simplified();
        okay = !temp.isEmpty();
        if(okay)
        {
            double val = temp.toDouble(&okay) * 0.01f;
            if(okay)
                labelAtts->SetTextHeight1(val);
        }

        if(!okay)
        {
            ResettingError(tr("text height"),
                DoubleToQString(labelAtts->GetTextHeight1() * 100.));
            labelAtts->SetTextHeight1(labelAtts->GetTextHeight1());
        }
    }

    // Do textHeight2
    if(which_widget == LabelAttributes::ID_textHeight2 || doAll)
    {
        temp = textHeight2SpinBox->text();
        int plen = (temp.indexOf(textHeight2SpinBox->prefix()) != -1) ? 
            textHeight2SpinBox->prefix().length() : 0;
        int slen = (temp.indexOf(textHeight2SpinBox->suffix()) != -1) ? 
            textHeight2SpinBox->suffix().length() : 0;
        temp = temp.mid(plen, temp.length() - plen - slen).simplified();
        okay = !temp.isEmpty();
        if(okay)
        {
            double val = temp.toDouble(&okay)*0.01f;
            if(okay)
                labelAtts->SetTextHeight2(val);
        }

        if(!okay)
        {
            ResettingError(tr("text height"),
                DoubleToQString(labelAtts->GetTextHeight2() * 100.));
            labelAtts->SetTextHeight2(labelAtts->GetTextHeight2());
        }
    }

    // Do formatTemplate
    if(which_widget == LabelAttributes::ID_formatTemplate || doAll)
    {
        okay = true;

        std::string temp = formatTemplate->displayText().trimmed().toStdString();

        // Test the new value and don't apply it if it's an invalid printf
        // string. In practice snprintf never throws an error for wrong
        // type or number of %f slots.
        if (!StringHelpers::ValidatePrintfFormatString(temp.c_str(), "float"))
        {
            Message(tr("Must enter a printf-style template that would be valid for a single floating point number."));
            okay = false;
        }

        if (okay)
        {
            char test[36];
            int len = SNPRINTF(test, 36, temp.c_str(), 0.0f);
            if (len >= 35)
            {
                Message(tr("The template produces values that are too long.  36 character limit."));
                okay = false;
            }
        }

        if(okay)
            labelAtts->SetFormatTemplate(temp);
        else
        {
            ResettingError(tr("Format template"),
                QString(labelAtts->GetFormatTemplate().c_str()));
            labelAtts->SetFormatTemplate(labelAtts->GetFormatTemplate());
        }
    }
}

// ****************************************************************************
// Method: QvisLabelPlotWindow::Apply
//
// Purpose: 
//   Called to apply changes in the subject.
//
// Programmer: Brad Whitlock
// Creation:   Thu Oct 21 18:18:16 PST 2004
//
// Modifications:
//   
// ****************************************************************************

void
QvisLabelPlotWindow::Apply(bool ignore)
{
    if(AutoUpdate() || ignore)
    {
        GetCurrentValues(-1);
        labelAtts->Notify();

        GetViewerMethods()->SetPlotOptions(plotType);
    }
    else
        labelAtts->Notify();
}


//
// Qt Slot functions
//


// ****************************************************************************
// Method: QvisLabelPlotWindow::apply
//
// Purpose: 
//   Qt slot function called when apply button is clicked.
//
// Programmer: Brad Whitlock
// Creation:   Thu Oct 21 18:18:16 PST 2004
//
// Modifications:
//   
// ****************************************************************************

void
QvisLabelPlotWindow::apply()
{
    Apply(true);
}


// ****************************************************************************
// Method: QvisLabelPlotWindow::makeDefault
//
// Purpose: 
//   Qt slot function called when "Make default" button is clicked.
//
// Programmer: Brad Whitlock
// Creation:   Thu Oct 21 18:18:16 PST 2004
//
// Modifications:
//   
// ****************************************************************************

void
QvisLabelPlotWindow::makeDefault()
{
    GetCurrentValues(-1);
    labelAtts->Notify();
    GetViewerMethods()->SetDefaultPlotOptions(plotType);
}


// ****************************************************************************
// Method: QvisLabelPlotWindow::reset
//
// Purpose: 
//   Qt slot function called when reset button is clicked.
//
// Programmer: Brad Whitlock
// Creation:   Thu Oct 21 18:18:16 PST 2004
//
// Modifications:
//   
// ****************************************************************************

void
QvisLabelPlotWindow::reset()
{
    GetViewerMethods()->ResetPlotOptions(plotType);
}


void
QvisLabelPlotWindow::showNodesToggled(bool val)
{
    labelAtts->SetShowNodes(val);
    SetUpdate(false);
    Apply();
}


void
QvisLabelPlotWindow::showCellsToggled(bool val)
{
    labelAtts->SetShowCells(val);
    SetUpdate(false);
    Apply();
}


void
QvisLabelPlotWindow::restrictNumberOfLabelsToggled(bool val)
{
    labelAtts->SetRestrictNumberOfLabels(val);
    Apply();
}

void
QvisLabelPlotWindow::numberOfLabelsChanged(int val)
{
    labelAtts->SetNumberOfLabels(val);
    SetUpdate(false);
    Apply();
}

void
QvisLabelPlotWindow::drawLabelsFacingChanged(int val)
{
    if(val != labelAtts->GetDrawLabelsFacing())
    {
        labelAtts->SetDrawLabelsFacing(LabelAttributes::LabelDrawFacing(val));
        SetUpdate(false);
        Apply();
    }
}

void
QvisLabelPlotWindow::legendToggled(bool val)
{
    labelAtts->SetLegendFlag(val);
    SetUpdate(false);
    Apply();
}

void
QvisLabelPlotWindow::labelDisplayFormatChanged(int val)
{
    if(val != labelAtts->GetLabelDisplayFormat())
    {
        labelAtts->SetLabelDisplayFormat(LabelAttributes::LabelIndexDisplay(val));
        SetUpdate(false);
        Apply();
    }
}

void
QvisLabelPlotWindow::textColor1Changed(const QColor &color)
{
    ColorAttribute temp(color.red(), color.green(), color.blue());
    labelAtts->SetTextColor1(temp);
    SetUpdate(false);
    Apply();
}

void
QvisLabelPlotWindow::textColor2Changed(const QColor &color)
{
    ColorAttribute temp(color.red(), color.green(), color.blue());
    labelAtts->SetTextColor2(temp);
    SetUpdate(false);
    Apply();
}

void
QvisLabelPlotWindow::specifyTextColor1Toggled(bool val)
{
    labelAtts->SetSpecifyTextColor1(val);
    Apply();
}

void
QvisLabelPlotWindow::specifyTextColor2Toggled(bool val)
{
    labelAtts->SetSpecifyTextColor2(val);
    Apply();
}

void
QvisLabelPlotWindow::textHeight1Changed(double val)
{
    float textHeight = val * 0.01f;
    labelAtts->SetTextHeight1(textHeight);
    SetUpdate(false);
    Apply();
}

void
QvisLabelPlotWindow::textHeight2Changed(double val)
{
    float textHeight = val * 0.01f;
    labelAtts->SetTextHeight2(textHeight);
    SetUpdate(false);
    Apply();
}

void
QvisLabelPlotWindow::horizontalJustificationChanged(int val)
{
    if(val != labelAtts->GetHorizontalJustification())
    {
        labelAtts->SetHorizontalJustification(LabelAttributes::LabelHorizontalAlignment(val));
        SetUpdate(false);
        Apply();
    }
}

void
QvisLabelPlotWindow::verticalJustificationChanged(int val)
{
    if(val != labelAtts->GetVerticalJustification())
    {
        labelAtts->SetVerticalJustification(LabelAttributes::LabelVerticalAlignment(val));
        SetUpdate(false);
        Apply();
    }
}

void
QvisLabelPlotWindow::depthTestButtonGroupChanged(int val)
{
    labelAtts->SetDepthTestMode((LabelAttributes::DepthTestMode)val);
    SetUpdate(false);
    Apply();
}


void 
QvisLabelPlotWindow::formatTemplateChanged()
{
    bool okay = true;

    std::string newval = formatTemplate->displayText().trimmed().toStdString();

    //Test the new value and don't apply it if it's an invalid printf string.
    //In practice snprintf never throws an error for wrong type or number
    //of %f slots.
    if (!StringHelpers::ValidatePrintfFormatString(newval.c_str(), "float"))
    {
        Message(tr("Must enter a printf-style template that would be valid for a single floating point number."));
        okay = false;
    }
    
    if (okay)
    {
        char test[36];
        int len = SNPRINTF(test, 36, newval.c_str(), 0.0f);
        if (len >= 35)
        {
            Message(tr("The template produces values that are too long.  36 character limit."));
            okay = false;
        }
    }

    if(okay)
    {
        labelAtts->SetFormatTemplate(newval);
        SetUpdate(false);
        Apply();
    }
    else
    {
        ResettingError(tr("Format template"),
            QString(labelAtts->GetFormatTemplate().c_str()));
        labelAtts->SetFormatTemplate(labelAtts->GetFormatTemplate());
        labelAtts->Notify();
    }
}



