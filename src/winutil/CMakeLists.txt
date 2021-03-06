#*****************************************************************************
#
# Copyright (c) 2000 - 2017, Lawrence Livermore National Security, LLC
# Produced at the Lawrence Livermore National Laboratory
# LLNL-CODE-442911
# All rights reserved.
#
# This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
# full copyright notice is contained in the file COPYRIGHT located at the root
# of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
#
# Redistribution  and  use  in  source  and  binary  forms,  with  or  without
# modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of  source code must  retain the above  copyright notice,
#    this list of conditions and the disclaimer below.
#  - Redistributions in binary form must reproduce the above copyright notice,
#    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
#    documentation and/or other materials provided with the distribution.
#  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
#    be used to endorse or promote products derived from this software without
#    specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
# ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
# LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
# DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
# SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
# CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
# LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
# OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
# DAMAGE.
#
# Modifications:
#   Kathleen Bonnell, Mon Jan 17 17:42:15 MST 2011
#   Add QvisColorTableWidget.
#
#   Kathleen Biagas, Fri Aug 8 08:52:46 PDT 2014
#   Added QvisNoDefaultColorTableButton.
#
#   Kathleen Biagas, Mon Mar 14 13:51:16 PDT 2016
#   With QT 5 on linux, link with Qt's X11Extras library.
#
#****************************************************************************/

SET(WINUTIL_SOURCES
Appearance.C
QvisColorTableButton.C
QvisNoDefaultColorTableButton.C
QvisColorTableWidget.C
QvisVariableButton.C
QvisVariableButtonHelper.C
QvisVariablePopupMenu.C
UnicodeHelper.C
VariableMenuPopulator.C
WindowMetrics.C
)

# List the files that we'll run moc on
SET(WINUTIL_MOC_SOURCES
QvisColorTableButton.h
QvisNoDefaultColorTableButton.h
QvisColorTableWidget.h
QvisVariableButton.h
QvisVariableButtonHelper.h
QvisVariablePopupMenu.h
)
QT_WRAP_CPP(WINUTIL WINUTIL_SOURCES ${WINUTIL_MOC_SOURCES})

INCLUDE_DIRECTORIES(
${VISIT_COMMON_INCLUDES}
${VISIT_SOURCE_DIR}/winutil
${VISIT_SOURCE_DIR}/avt/DBAtts/MetaData
${VISIT_SOURCE_DIR}/avt/DBAtts/SIL
${VTK_INCLUDE_DIRS}
${QT_INCLUDE_DIR}
${QT_QTCORE_INCLUDE_DIR}
${QT_QTGUI_INCLUDE_DIR}
${QT_QTOPENGL_INCLUDE_DIR}
)

# Add link directories needed to use Qt.
LINK_DIRECTORIES(${LIBRARY_OUTPUT_DIRECTORY} ${QT_LIBRARY_DIR})

ADD_LIBRARY(winutil ${WINUTIL_SOURCES})

# Specify the libraries to link against on Windows & Mac
TARGET_LINK_LIBRARIES(winutil visitcommon avtdbatts ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
if(VISIT_QT5 AND LINUX)
    target_link_libraries(winutil ${QT_QTX11EXTRAS_LIBRARY})
ENDIF()

VISIT_INSTALL_TARGETS(winutil)
