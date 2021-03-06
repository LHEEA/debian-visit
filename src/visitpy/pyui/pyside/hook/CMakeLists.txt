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
#    Kathleen Biagas, Tue Jan 24 11:05:25 PST 2017
#    Add support for Qt5.
#
#*****************************************************************************

set(pyside_hook_sources "")
set(pyside_hook_gen_sources
    ${CMAKE_CURRENT_BINARY_DIR}/pyside_hook/pysidehook_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/pyside_hook/pyside_hook_module_wrapper.cpp)

if(VISIT_QT5)
    set(pyside_hook_include_paths ${Qt5Core_INCLUDE_DIRS})
else()
    set(pyside_hook_include_paths ${QT_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR})
endif()

set(pyside_hook_link_libs ${QT_QTCORE_LIBRARY})

#
# If we enable eavl, it will appear in the link line, so add ${EAVL_LIBRARY_DIR}
#
IF(EAVL_FOUND)
    LINK_DIRECTORIES(${EAVL_LIBRARY_DIR})
ENDIF()

PYSIDE_ADD_MODULE(pyside_hook
                  site-packages/visit
                  pyside_hook_sources
                  pyside_hook_gen_sources
                  pyside_hook_include_paths
                  pyside_hook_link_libs
                  global.h typesystem.xml)

