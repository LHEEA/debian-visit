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
#   Kathleen Bonnell, Wed Jan 05 10:25:13 PST 2010
#   Add FOLDER property.
#
#****************************************************************************/

SET(XMLEDIT_SOURCES
XMLEditMain.C
XMLDocument.C
XMLEdit.C
XMLEditAttribute.C
XMLEditPlugin.C
XMLEditEnums.C
XMLEditFields.C
XMLEditFunctions.C
XMLEditCode.C
XMLEditCodeGeneratorWindow.C
XMLEditCodeSelectionDialog.C
XMLEditConstants.C
XMLEditIncludes.C
XMLEditMakefile.C
)

SET(XMLEDIT_MOC_SOURCES
XMLEdit.h
XMLEditAttribute.h
XMLEditPlugin.h
XMLEditEnums.h
XMLEditFields.h
XMLEditFunctions.h
XMLEditCode.h
XMLEditCodeGeneratorWindow.h
XMLEditCodeSelectionDialog.h
XMLEditConstants.h
XMLEditIncludes.h
XMLEditMakefile.h
)
QT_WRAP_CPP(xmledit XMLEDIT_SOURCES ${XMLEDIT_MOC_SOURCES})

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_COMMON_INCLUDES}
${VISIT_SOURCE_DIR}/tools/xml
${QT_INCLUDE_DIR}
${QT_QTCORE_INCLUDE_DIR}
${QT_QTGUI_INCLUDE_DIR}
${QT_QTXML_INCLUDE_DIR}
)

LINK_DIRECTORIES(${QT_LIBRARY_DIR})

IF(APPLE)
    ADD_EXECUTABLE(xmledit MACOSX_BUNDLE ${XMLEDIT_SOURCES})
    SET(MACOSX_BUNDLE_BUNDLE_NAME          "XmlEdit ${VISIT_VERSION}")
    SET(MACOSX_BUNDLE_INFO_STRING          "Editor for VisIt plugin XML files")
    SET(MACOSX_BUNDLE_ICON_FILE            ${VISIT_SOURCE_DIR}/common/icons/VisItIcon.icns)
    SET_SOURCE_FILES_PROPERTIES(${VISIT_SOURCE_DIR}/common/icons/VisItIcon.icns
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )
    SET(MACOSX_BUNDLE_GUI_IDENTIFIER       VISI)
    SET(MACOSX_BUNDLE_LONG_VERSION_STRING  "XmlEdit version ${VISIT_VERSION}")
    SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "XmlEdit ${VISIT_VERSION}")
    SET(MACOSX_BUNDLE_BUNDLE_VERSION       ${VISIT_VERSION})
    SET(MACOSX_BUNDLE_COPYRIGHT            "Copyright (c) 2000 - 2017, Lawrence Livermore National Security, LLC")
ELSE(APPLE)
    ADD_EXECUTABLE(xmledit ${VISIT_APPLICATION_STYLE} ${XMLEDIT_SOURCES})
ENDIF(APPLE)

SET(RELEVANT_QT_LIBS 
${QT_QTGUI_LIBRARY}
${QT_QTXML_LIBRARY}
${QT_QTCORE_LIBRARY}
)
IF(VISIT_STATIC)
    MAC_NIB_INSTALL(xmledit)
    SET(RELEVANT_QT_LIBS
        ${RELEVANT_QT_LIBS}
        ${QT_QTGUI_LIB_DEPENDENCIES}
        ${QT_QTXML_LIB_DEPENDENCIES}
        ${QT_QTCORE_LIB_DEPENDENCIES}
    )
ENDIF(VISIT_STATIC)

TARGET_LINK_LIBRARIES(xmledit ${RELEVANT_QT_LIBS})

VISIT_INSTALL_TARGETS(xmledit)
VISIT_TOOLS_ADD_FOLDER(xml xmledit)
