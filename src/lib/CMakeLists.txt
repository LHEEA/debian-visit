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
#
#****************************************************************************/

#-----------------------------------------------------------------------------
# Runtime loading of Mesa relies on having OSMesa in a known path.
#
# For development builds we create symlink to libOSMesa along side
# VisIt's libraries.
#
# I (Cyrus) am not sure how this will work on windows - there may be a
# more general solution.
#
# For a 'make install'ed version libOSMesa should be properly installed
# by our install targets.
#
# Modifications:
#    Jeremy Meredith, Wed Jan 20 11:27:30 EST 2010
#    I added a command to put a symlink to python in the lib directory.
#    We need this to set python-related environment variables in
#    internallauncher.  I don't know if this is a good solution, as I
#    don't know the implication for an installed setup -- this is only
#    intended to fix running inside a development build.
#
#    Cyrus Harrison, Wed Feb  3 10:10:22 PST 2010
#    Add symlinks to allow us to locate the vtk python wrapper module.
#
#    Kathleen Bonnell, Wed Mar 17 10:08:17 MST 2010 
#    Use FILE(COPY ...) on windows, as windows doesn't support symlinks.
#    Handled python filters on windows differently, as the VTK directory 
#    structure is different.
#
#    Cyrus Harrison, Wed Jul  7 10:09:07 PDT 2010
#    Remove any existing symlinks before attempting to create new ones.
#
#    Kathleen Biagas, Thu May 10 10:58:39 MST 2012 
#    Change how python is handled on Windows to reflect recent changes.
#
#    Kathleen Biagas, Thu June 14 15:53:12 MST 2012 
#    Add target for pyside on windows.
#
#    Gunther H. Weber, Thu Nov 21 18:26:51 PST 2013
#    Use ${PYSIDE_PYTHONPATH} (set by findpackage PySide) instead of 
#    ${VISIT_PYSIDE_DIR}/lib/site-packages to support system PySide installs
#
#----------------------------------------------------------------------------

IF(MESA_FOUND)
    IF (NOT WIN32)
        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E make_directory
                        ${CMAKE_CURRENT_BINARY_DIR}/osmesa
                        RESULT_VARIABLE GEN_OSMESA_DIR)
        #
        # make sure lib/osmesa exists before we try to
        # symlink OSMesa.so as libGL.so
        #
        IF(NOT "${GEN_OSMESA_DIR}" STREQUAL "0")
            MESSAGE(WARNING "Failed to create lib/osmesa/")
        ENDIF(NOT "${GEN_OSMESA_DIR}" STREQUAL "0")

        ## TODO:
        ## We need to use SONAME of the detected GL lib.
        ## Not sure how to best approach this.
        ## I don't think the strategy we use to find symlinks in ThirdPartyInstallLibrary
        ## will work for gl libs
        ##
        ## /usr/lib64/nvidia/libGL.so -> /usr/lib64/nvidia/libGL.so.304.43
        ## /usr/lib64/nvidia/libGL.so.1 -> /usr/lib64/nvidia/libGL.so.304.43
        ##
        ## In cmake we can detect, libGL.so, we can get the realpath /usr/lib64/nvidia/libGL.so.304.43
        ## BUT what we really need is "libGL.so.1", see:
        ##
        ## rzalastor2@cyrush: objdump /usr/lib64/nvidia/libGL.so.304.43 -p | grep SONAME
        ##   SONAME               libGL.so.1
        ##
        ## This is what all of the VTK libs link to (not libGL.so, or libGL.so.304.43)
        ## Since we want to pull a LD_LIB_PATH trick, we need to get this right.
        ##


        GET_FILENAME_COMPONENT(OSMESA_LIB_REAL ${MESA_LIBRARY_DIR}/${MESA_LIB} REALPATH)
        GET_FILENAME_COMPONENT(OSMESA_LIB_BASE ${OSMESA_LIB_REAL} NAME)

        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E remove -f
                                    ${CMAKE_CURRENT_BINARY_DIR}/osmesa/libGL.so)
        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E remove -f
                                    ${CMAKE_CURRENT_BINARY_DIR}/osmesa/libGL.so.1) # TODO USE SONAME HERE!

        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E create_symlink
                                ${MESA_LIBRARY_DIR}/${OSMESA_LIB_BASE}
                                ${CMAKE_CURRENT_BINARY_DIR}/osmesa/libGL.so)
        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E create_symlink
                                ${MESA_LIBRARY_DIR}/${OSMESA_LIB_BASE}
                                ${CMAKE_CURRENT_BINARY_DIR}/osmesa/libGL.so.1) # TODO USE SONAME HERE!
    ENDIF(NOT WIN32)
ENDIF(MESA_FOUND)



FOREACH(LIB ${R_LIB})
    IF (NOT WIN32)
        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E remove -f
                                ${CMAKE_CURRENT_BINARY_DIR}/${LIB})
        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E create_symlink
                                ${VISIT_R_DIR}/lib/${LIB}
                                ${CMAKE_CURRENT_BINARY_DIR}/${LIB})
    ELSE (NOT WIN32)
        FILE(COPY        ${VISIT_R_DIR}/lib/${LIB}
             DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    ENDIF (NOT WIN32)
ENDFOREACH(LIB in ${MESA_LIB})


IF(VISIT_PYTHON_DIR)
  IF (NOT WIN32)
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E remove -f
                            ${CMAKE_CURRENT_BINARY_DIR}/python)
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E create_symlink
                            ${VISIT_PYTHON_DIR}
                            ${CMAKE_CURRENT_BINARY_DIR}/python)
  ELSE (NOT WIN32)

    # because you don't need to choose your configuration up-front
    # on windows, make this a custom target so they are copied to the
    # correct lib/${CFG} directory
    ADD_CUSTOM_TARGET(python_lib ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${VISIT_PYTHON_DIR}/Lib
            ${VISIT_LIBRARY_DIR}/python/Lib
        COMMENT "Copying ${VISIT_PYTHON_DIR}/Lib/ ${VISIT_LIBRARY_DIR}/python/Lib")
    if(VISIT_NO_ALLBUILD)
        add_dependencies(visit_special_builds python_lib)
    endif()
  ENDIF (NOT WIN32)
ENDIF()

# prepare site-packages
IF(VISIT_PYTHON_FILTERS OR (VISIT_PYTHON_SCRIPTING AND HAVE_LIBPYSIDE))
    IF(NOT WIN32)
        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E make_directory
                        ${CMAKE_CURRENT_BINARY_DIR}/site-packages
                        RESULT_VARIABLE LIB_SITE_PKGS_MKDIR)
        #
        # make sure lib/site-packages exists before we try to
        # symlink or copy the vtk python wrappers
        #
        IF(NOT "${LIB_SITE_PKGS_MKDIR}" STREQUAL "0")
            MESSAGE(WARNING "Failed to create lib/site-packages/")
        ENDIF(NOT "${LIB_SITE_PKGS_MKDIR}" STREQUAL "0")
    ENDIF(NOT WIN32)
ENDIF(VISIT_PYTHON_FILTERS OR (VISIT_PYTHON_SCRIPTING AND HAVE_LIBPYSIDE))

IF(VISIT_PYTHON_FILTERS)
# We need to be able to locate the vtk python wrapper lib at run time.
# Place symlinks to its components in lib/site-packages/
    MESSAGE(STATUS "Adding VTK python wrappers to lib/site-packages/")
    IF (NOT WIN32)
        FILE(GLOB VTK_PYTHON_MODULE_ITEMS "${VISIT_VTK_DIR}/lib/python${PYTHON_VERSION}/site-packages/*")
        FOREACH(ITM ${VTK_PYTHON_MODULE_ITEMS})
            GET_FILENAME_COMPONENT(ITM_ABS ${ITM} ABSOLUTE)
            GET_FILENAME_COMPONENT(ITM_BASE ${ITM_ABS} NAME)
            MESSAGE(STATUS "Symlinking ${ITM_ABS} to ${CMAKE_CURRENT_BINARY_DIR}/site-packages/${ITM_BASE}")
            EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E remove -f
                                    ${CMAKE_CURRENT_BINARY_DIR}/site-packages/${ITM_BASE}
                                    RESULT_VARIABLE VTK_MODULE_SYM_RM)
            EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E create_symlink
                                    ${ITM_ABS}
                                    ${CMAKE_CURRENT_BINARY_DIR}/site-packages/${ITM_BASE}
                                    RESULT_VARIABLE VTK_MODULE_SYM_CREATE)
            IF(NOT "${VTK_MODULE_SYM_CREATE}" STREQUAL "0")
                MESSAGE(WARNING "Failed to create VTK Python module symlink in lib/site-packages/ for ${ITM_ABS}")
            ENDIF(NOT "${VTK_MODULE_SYM_CREATE}" STREQUAL "0")
        ENDFOREACH(ITM ${VTK_PYTHON_MODULE_ITEMS})
    ELSE (NOT WIN32)
        FILE(GLOB VTK_EGG_FILE "${VTK_PY_WRAPPERS_DIR}/site-packages/*egg*")
        # because you don't need to choose your configuration up-front
        # on windows, make this a custom target so they are copied to the
        # correct lib/${CFG} directory
        ADD_CUSTOM_TARGET(vtk_python_modules ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${VTK_PY_WRAPPERS_DIR}/site-packages/vtk
                    ${VISIT_LIBRARY_DIR}/site-packages/vtk
            COMMENT "Copying ${VTK_PY_WRAPPERS_DIR}/site-packages to ${VISIT_LIBRARY_DIR}/site-packages/vtk"
        )
        if(VISIT_NO_ALLBUILD)
            add_dependencies(visit_special_builds vtk_python_modules)
        endif()
    ENDIF (NOT WIN32)
ENDIF(VISIT_PYTHON_FILTERS)

IF(VISIT_PYTHON_SCRIPTING AND HAVE_LIBPYSIDE)
    MESSAGE(STATUS "Adding PySide to lib/site-packages/")
    IF (NOT WIN32)
        FILE(GLOB PYSIDE_MODULE_ITEMS "${PYSIDE_PYTHONPATH}/*")
        FOREACH(ITM ${PYSIDE_MODULE_ITEMS})
            GET_FILENAME_COMPONENT(ITM_ABS ${ITM} ABSOLUTE)
            GET_FILENAME_COMPONENT(ITM_BASE ${ITM_ABS} NAME)
            MESSAGE(STATUS "Symlinking ${ITM_ABS} to ${CMAKE_CURRENT_BINARY_DIR}/site-packages/${ITM_BASE}")
            EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E remove -f
                          ${CMAKE_CURRENT_BINARY_DIR}/site-packages/${ITM_BASE}
                          RESULT_VARIABLE PYSIDE_MODULE_SYM_RM)
            EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E create_symlink
                          ${ITM_ABS}
                          ${CMAKE_CURRENT_BINARY_DIR}/site-packages/${ITM_BASE}
                          RESULT_VARIABLE PYSIDE_MODULE_SYM_CREATE)
            IF(NOT "${PYSIDE_MODULE_SYM_CREATE}" STREQUAL "0")
                MESSAGE(WARNING "Failed to create PySide module symlink in lib/site-packages/ for ${ITM_ABS}")
            ENDIF(NOT "${PYSIDE_MODULE_SYM_CREATE}" STREQUAL "0")
        ENDFOREACH(ITM ${PYSIDE_MODULE_ITEMS})
    ELSE (NOT WIN32)
      if(VISIT_QT5)
        set(pysidename "PySide2")
      else()
        set(pysidename "PySide")
      endif()
      ADD_CUSTOM_TARGET(pyside_modules ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${PYSIDE_PYTHONPATH}/${pysidename}
                    ${VISIT_LIBRARY_DIR}/site-packages/${pysidename}
            COMMENT "Copying ${PYSIDE_PYTHONPATH}/${pysidename} to ${VISIT_LIBRARY_DIR}/site-packages/${pysidename}"
        )
        if(VISIT_NO_ALLBUILD)
            add_dependencies(visit_special_builds pyside_modules)
        endif()
    ENDIF (NOT WIN32)
ENDIF(VISIT_PYTHON_SCRIPTING AND HAVE_LIBPYSIDE)

