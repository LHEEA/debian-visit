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
#   Eric Brugger, Fri Jan 22 16:51:39 PST 2010
#   I added the data generator unic, which generates UNIC test data.
#
#   Mark C. Miller, Fri Jan 22 16:40:43 PST 2010
#   Added function LINK_DATA_TARGETS and invokation to create sesame.pdb.lnk
#   and largefile.silo.lnk.
#
#   Mark C. Miller, Fri Jan 22 17:27:47 PST 2010
#   Removed preceding change to satisfy purists ;)
#
#   Cyrus Harrison, Mon Feb  1 12:46:56 PST 2010
#   Added missing visit includes to basic targets.
#
#   Brad Whitlock, Wed Feb 10 14:44:23 PST 2010
#   I added Velodyne test data.
#
#   Eric Brugger, Thu Mar 11 15:04:16 PST 2010
#   I added logic to create the example data files for a visit distribution
#   if the file visit_dist_data.tar.gz was not present.
#
#   Eric Brugger, Fri Mar 12 13:08:21 PST 2010
#   I added dependencies and additional outputs to the custom commands I
#   added yesterday so that parallel builds would work and make clean would
#   remove all the files.
#
#   Mark C. Miller, Fri Apr 23 23:51:46 PDT 2010
#   Use glob to produce list of archived targets. That way, don't have to
#   edit this makefile every time one is added or removed.
#
#   Brad Whitlock, Thu Apr 29 11:50:42 PDT 2010
#   I added xdmf2d.C.
#
#   Eric Brugger, Thu Jun 17 15:24:51 PDT 2010
#   I added logic to only create the Silo data files if VisIt is being
#   built with the Silo library.
#
#   Kathleen Bonnell, Mon Nov 15 15:46:11 MST 2010
#   Add support for building on windows.
#
#   Cyrus Harrison, Wed Feb  9 11:20:26 PST 2011
#   Fix install of data files from out of source build.
#
#   Eric Brugger, Fri Nov 18 14:52:52 PST 2011
#   I added xdmf_binary.C.
#
#   Eric Brugger, Fri Oct 18 14:55:19 PDT 2013
#   I changed the name of the test target to testdata, since test no longer
#   works with cmake 2.8.10.2.
#
#   Kathleen Biagas, Tue Nov 25 18:06:23 MST 2014
#   Add /STACK Link flag to multi_test target on Windows so it will run
#   properly.  Reworked the create_data_examples targets so things work
#   correctly on Windows.
#
#   Eric Brugger, Wed Sep 20 17:35:37 PDT 2017
#   Modify the script to untar files of the name "*test_data*.tar.gz" instead
#   of just "*test_data.tar.gz".
#
#****************************************************************************/

cmake_minimum_required(VERSION 2.8)

IF(WIN32)
    PROJECT(VISIT_DATA)
ENDIF(WIN32)

#-----------------------------------------------------------------------------
# If this directory exists the root CMakeLists.txt adds this directroy as a 
# subdirectory to the main VisIt project.
#
# Prevent users from running cmake directy in this directory.
#-----------------------------------------------------------------------------
IF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    MESSAGE(FATAL_ERROR "VisIt's \"data\" directory cannot be configured "
                    "independently from the main \"src\" directory. Please "
                    "run cmake on VisIt's \"src\" directory.")
ENDIF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")


MESSAGE(STATUS "Configuring VisIt Data Targets")

#-----------------------------------------------------------------------------
# BUILD_DATA_TARGET cmake function
# Helper function that compiles & links a data generator program.
# Usage:
#  BUILD_DATA_TARGET( target_name
#                    INCLUDE_DIRS
#                     path/to/includes
#                     path/to/more/includes
#                    LIB_DIRS
#                     path/to/libs
#                     path/to/more/libs
#                    LIBS
#                     lib_names
#                    DEFS
#                     definitions (eg. Preprocessor for windows)
#
# Source files are detected in two ways:
#  If ${target_name}_SOURCES is set:  its contents are used.
#  Otherwise: ${target_name}.C is used.
#
#-----------------------------------------------------------------------------
FUNCTION(BUILD_DATA_TARGET_IMPL target_name do_parallel)
    SET(target_SOURCES "")
    SET(target_INCLUDE_DIRS "")
    SET(target_LIB_DIRS "")
    SET(target_LIBS "")
    SET(target_DEFS "")

    # cmake gymnastics to implement optional argument sections:
    FOREACH(ARG ${ARGN})
        IF(${ARG} STREQUAL "INCLUDE_DIRS" OR
           ${ARG} STREQUAL "LIB_DIRS" OR
           ${ARG} STREQUAL "LIBS" OR
           ${ARG} STREQUAL "DEFS")
            #switch var name to extend
            SET(ARG_VAR target_${ARG})
        ELSE()
            # add current arg into current varname
            SET("${ARG_VAR}" ${${ARG_VAR}} ${ARG})
        ENDIF()
    ENDFOREACH(ARG ${ARGN})

    INCLUDE_DIRECTORIES(${target_INCLUDE_DIRS})
    LINK_DIRECTORIES(${target_LIB_DIRS})

    # Automatically setup target_SOURCES if not set
    IF(DEFINED ${target_name}_SOURCES)
        SET(target_SOURCES "${${target_name}_SOURCES}")
    ELSE()
        SET(target_SOURCES ${target_name}.C)
    ENDIF()

    SET(tname ${target_name})
    IF("${do_parallel}" STREQUAL "ON")
        IF(VISIT_PARALLEL)
            SET(tname "${target_name}_par")
            ADD_PARALLEL_EXECUTABLE(${tname} ${target_SOURCES})
        ENDIF()
    ELSE()
        ADD_EXECUTABLE(${tname} ${target_SOURCES})
    ENDIF()

    ADD_DEFINITIONS(${target_DEFS})
    TARGET_LINK_LIBRARIES(${tname} ${target_LIBS})
    SET_TARGET_PROPERTIES(${tname}
                           PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                          )

ENDFUNCTION(BUILD_DATA_TARGET_IMPL target_name)

FUNCTION(BUILD_DATA_TARGET target_name)
    BUILD_DATA_TARGET_IMPL(${target_name} "OFF" ${ARGN})
ENDFUNCTION(BUILD_DATA_TARGET target_name)

FUNCTION(BUILD_PARALLEL_DATA_TARGET target_name)
    BUILD_DATA_TARGET_IMPL(${target_name} "ON" ${ARGN})
ENDFUNCTION(BUILD_PARALLEL_DATA_TARGET target_name)

#-----------------------------------------------------------------------------
# Data Generation Program Targets
#
# This are build as part of the default target.
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Basic Data Gen Programs
#-----------------------------------------------------------------------------
SET(BASIC_TARGETS
bov
curve_builder
distribution_curves
mandelbulb
xdmf_binary
)

SET(BASIC_TARGETS_PAR
mandelbulb
)

#-----------------------------------------------------------------------------
# VTK Gen Programs
#-----------------------------------------------------------------------------
SET(VTK_TARGETS degen_meshes)

#-----------------------------------------------------------------------------
# HDF5 Data Gen Programs
#-----------------------------------------------------------------------------
SET(HDF5_TARGETS unic xdmf xdmf2d)

#-----------------------------------------------------------------------------
# PDB Data Gen Programs
#-----------------------------------------------------------------------------
SET(PDB_TARGETS
correlationtest
pdbdatabase
streak
)

#-----------------------------------------------------------------------------
#  Setup {TARGET}_SOURCES for targets with multiple source files.
#-----------------------------------------------------------------------------
SET(correlationtest_SOURCES correlationtest.C pdbdatabase_link.C)
SET(pdbdatabase_SOURCES pdbdatabase.C pdbdatabase_link.C)
SET(streak_SOURCES streak.C pdbdatabase_link.C)

#-----------------------------------------------------------------------------
# Silo Data Gen Programs
#-----------------------------------------------------------------------------
SET(SILO_TARGETS
arbpoly
bigsil
bounce
big_quads
csg
emptydomains
fullframe
galaxy
ghost
global_node
globe
largefile
lineout_test
lowfrac
mat_3x3_3across
mat_3x3x3_3across
meshorigin
mmadj_rect_2d
multi_test
multidir
noise
noise2d
non_conforming
one_quad
quad_disk
sid97
specmix
specmix_double
testall
thinplane
tire
wave
)

#-----------------------------------------------------------------------------
#  Setup {TARGET}_SOURCES for targets with multiple source files.
#-----------------------------------------------------------------------------
SET(noise_SOURCES noise.C QuadMesh.C)
SET(multidir_SOURCES multidir.C QuadMesh.C)


#-----------------------------------------------------------------------------
# Build all Basic Targets
#-----------------------------------------------------------------------------
FOREACH(BASIC_TARGET ${BASIC_TARGETS})
   BUILD_DATA_TARGET(${BASIC_TARGET}
                     INCLUDE_DIRS
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ${VISIT_BINARY_DIR}/include
                     ${VISIT_SOURCE_DIR}/include)
ENDFOREACH(BASIC_TARGET ${BASIC_TARGETS})

FOREACH(BASIC_TARGET ${BASIC_TARGETS_PAR})
   BUILD_PARALLEL_DATA_TARGET(${BASIC_TARGET}
                     INCLUDE_DIRS
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ${VISIT_BINARY_DIR}/include
                     ${VISIT_SOURCE_DIR}/include)
ENDFOREACH(BASIC_TARGET ${BASIC_TARGETS_PAR})

#-----------------------------------------------------------------------------
# Build all VTK Targets
#-----------------------------------------------------------------------------
FOREACH(VTK_TARGET ${VTK_TARGETS})
    BUILD_DATA_TARGET(${VTK_TARGET}
                  INCLUDE_DIRS
                    ${VTK_INCLUDE_DIRS}
                  LIB_DIRS
                    ${VTK_LIBRARY_DIRS}
                  LIBS
                    vtkIOLegacy
                 )
ENDFOREACH(VTK_TARGET ${VTK_TARGETS})

#-----------------------------------------------------------------------------
# If we have HDF5 build all HDF5 Data Gen Target Programs
#-----------------------------------------------------------------------------
IF(HDF5_FOUND)
    FOREACH(HDF5_TARGET ${HDF5_TARGETS})
        BUILD_DATA_TARGET(${HDF5_TARGET}
                          INCLUDE_DIRS
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${HDF5_INCLUDE_DIR}
                          LIB_DIRS
                            ${HDF5_LIBRARY_DIR}
                          LIBS
                            ${HDF5_LIB}
                         )
    ENDFOREACH()
ENDIF(HDF5_FOUND)

#-----------------------------------------------------------------------------
# If we have Silo build all Silo & PDB Data Gen Programs
#-----------------------------------------------------------------------------
IF(SILO_FOUND)
    # Build PDB Targets (The required pdb symbols live in Silo's libs.)
    FOREACH(PDB_TARGET ${PDB_TARGETS})
        BUILD_DATA_TARGET(${PDB_TARGET}
                          INCLUDE_DIRS
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${VISIT_BINARY_DIR}/include
                            ${VISIT_SOURCE_DIR}/include
                          LIB_DIRS
                            ${PDB_LIBRARY_DIR}
                        LIBS
                            ${PDB_LIB}
                        )
    ENDFOREACH()
    # Build Silo Targets
    FOREACH (SILO_TARGET ${SILO_TARGETS})
        BUILD_DATA_TARGET(${SILO_TARGET}
                          INCLUDE_DIRS
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${SILO_INCLUDE_DIR}
                            ${VISIT_SOURCE_DIR}/common/utility
                        LIB_DIRS
                            ${SILO_LIBRARY_DIR}
                        LIBS
                            ${SILO_LIB}
                        )
    ENDFOREACH()
    if(WIN32)
      set_target_properties(multi_test PROPERTIES LINK_FLAGS "/STACK:8000000")
    endif()
ENDIF(SILO_FOUND)

#-----------------------------------------------------------------------------
# Setup the Data Generation Target.
#-----------------------------------------------------------------------------
# We have a single target "testdata" that generates all of our test data.
# This untars all archived datasets.
#-----------------------------------------------------------------------------


#-----------------------------------------------------------------------------
# Discover the proper untar command.
#
# "cmake -E tar" supports untaring for normal & gzipped tarballs.
# Unfortunately it is very slow so we only use it as a fallback. It also
# fails on Windows for many of our .tar.gz data files.
#
#  Kathleen Biagas, Wed Oct  2 14:19:36 PDT 2013
#  Added PROGRAM6432 env var to search as I discovered that 32-bit cmake
#  running on 64-bit Windows 8 reports 'Program Files (x86)' for 
#  'ENV${PROGRAMFILES}'.
#
#-----------------------------------------------------------------------------
IF(NOT WIN32)
    FIND_PROGRAM(TAR_EXE tar)
    IF(NOT "${TAR_EXE}" STREQUAL "TAR_EXE-NOTFOUND")
        SET(UNTAR_CMD ${TAR_EXE})
        SET(UNTAR_ARGS "-xzvf")
    ELSE()
        SET(UNTAR_CMD ${CMAKE_COMMAND})
        SET(UNTAR_ARGS "-E tar -xzvf")
    ENDIF()
ELSE(NOT WIN32)
   # There used to be limitations in cmake's untar, even winzip's command line,
   # so 7-zip was utilized.  Recent versions of 7-zip now handle symlinks on
   # windows. Cool! but the functionality requires 7-zip be run as-admin or
   # have a special group-policy set that allows symlink creation otherwise the
   # extraction fails.  So, now only use 7-zip if requested. 
   # 
   if(VISIT_USE_7ZIP)
       set(PF1 "PROGRAMFILES")
       set(PF2 "PROGRAMFILES(X86)")
       FIND_PROGRAM(SEVEN_ZIP_EXE 7z "${VISIT_SEVEN_ZIP_DIR}" 
                                     "$ENV{${PF1}}/7-Zip" 
                                     "$ENV{${PF2}}/7-Zip")
       unset(PF2)
       unset(PF1)
       if("${SEVEN_ZIP_EXE}" STREQUAL "SEVEN_ZIP_EXE-NOTFOUND")
           MESSAGE(WARNING "7-Zip not found, .tar.gz data files will not be extracted.")
       endif()
   endif()
ENDIF(NOT WIN32)


#-----------------------------------------------------------------------------
# Create the list of archived data targets.
#
# Each archived target extracts data into a directory matching the root name
# of the source tarball. This makes tracking the dependencies simple.
#
#-----------------------------------------------------------------------------
FILE(GLOB ARCHIVED_TARGETS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test_data*.tar.gz)

#-----------------------------------------------------------------------------
# Add a custom command to extract each archived dataset & collect
# output directory names in a dependency list.
#-----------------------------------------------------------------------------
SET(DATA_TARGET_DEPENDS "")

FOREACH(DATASET_TARGET_FILE ${ARCHIVED_TARGETS})
    STRING(REPLACE ".tar.gz" "" DATASET_TARGET "${DATASET_TARGET_FILE}")

    IF(NOT WIN32)
        ADD_CUSTOM_COMMAND(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${DATASET_TARGET}
            COMMAND ${UNTAR_CMD}
            ARGS ${UNTAR_ARGS} ${CMAKE_CURRENT_SOURCE_DIR}/${DATASET_TARGET_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )
    ELSE(NOT WIN32)
        if(VISIT_USE_7ZIP AND NOT "${SEVEN_ZIP_EXE}" STREQUAL "SEVEN_ZIP_EXE-NOTFOUND")
            # With 7-zip, first command extracts the tar file part, the second 
            # extracts the data files from the tarball.
            # We then must delete the .tar file
            ADD_CUSTOM_COMMAND(
                OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${DATASET_TARGET}
                COMMAND ${SEVEN_ZIP_EXE} x -y ${CMAKE_CURRENT_SOURCE_DIR}/${DATASET_TARGET_FILE}
                COMMAND ${SEVEN_ZIP_EXE} x -y ${DATASET_TARGET}.tar
                COMMAND del ${DATASET_TARGET}.tar
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                )
        else()
            ADD_CUSTOM_COMMAND(
                OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${DATASET_TARGET}
                COMMAND ${CMAKE_COMMAND} -E tar -xzvf ${CMAKE_CURRENT_SOURCE_DIR}/${DATASET_TARGET_FILE}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )
        endif()
    ENDIF (NOT WIN32)
    SET( DATA_TARGET_DEPENDS ${DATA_TARGET_DEPENDS} ${CMAKE_CURRENT_BINARY_DIR}/${DATASET_TARGET})
ENDFOREACH()

#-----------------------------------------------------------------------------
# Add custom targets: "data" & "testdata"
#-----------------------------------------------------------------------------
ADD_CUSTOM_TARGET(data DEPENDS ${DATA_TARGET_DEPENDS})
ADD_CUSTOM_TARGET(testdata)
ADD_DEPENDENCIES(testdata data)

#-----------------------------------------------------------------------------
# Add install command for contents of "data"
#-----------------------------------------------------------------------------

IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/visit_dist_data.tar.gz)
    IF(NOT WIN32)
        SET(DIST_UNTAR_CMD "${UNTAR_CMD} ${UNTAR_ARGS} ${CMAKE_CURRENT_SOURCE_DIR}/visit_dist_data.tar.gz")

        INSTALL(CODE "execute_process(COMMAND ${DIST_UNTAR_CMD} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )")
    ELSE(NOT WIN32)
        IF(VISIT_USE_7ZIP AND NOT "${SEVEN_ZIP_EXE}" STREQUAL "SEVEN_ZIP_EXE-NOTFOUND")
            SET (DIST_UNTAR_CMD1 "\"${SEVEN_ZIP_EXE}\" x -y \"${CMAKE_CURRENT_SOURCE_DIR}/visit_dist_data.tar.gz\"")
            SET (DIST_UNTAR_CMD2 "\"${SEVEN_ZIP_EXE}\" x -y visit_dist_data.tar")
            SET (DIST_UNTAR_CMD3 "del /F visit_dist_data.tar")
            INSTALL(CODE "execute_process(COMMAND ${DIST_UNTAR_CMD1} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )")
            INSTALL(CODE "execute_process(COMMAND ${DIST_UNTAR_CMD2} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )")
            INSTALL(CODE "execute_process(COMMAND ${DIST_UNTAR_CMD3} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )")
        else()
            SET(DIST_UNTAR_CMD "${CMAKE_COMMAND} -E tar -xzvf ${CMAKE_CURRENT_SOURCE_DIR}/visit_dist_data.tar.gz")
            INSTALL(CODE "execute_process(COMMAND ${DIST_UNTAR_CMD} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )")
        endif()
    ENDIF(NOT WIN32)

    INSTALL(DIRECTORY
                ${CMAKE_CURRENT_BINARY_DIR}/visit_dist_data/
            DESTINATION
                data
            DIRECTORY_PERMISSIONS
                OWNER_READ OWNER_WRITE OWNER_EXECUTE
                GROUP_READ GROUP_WRITE GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE)
ELSE(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/visit_dist_data.tar.gz)
    IF(SILO_FOUND)
        SET(EXE_EXT "")
        SET(DATA_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
        SET(CMDS "")
        IF (WIN32)
            SET(EXE_EXT ".exe")
            SET(DATA_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
            FOREACH(SD ${SILO_LIBRARY_DIR})
              FOREACH(SL ${SILO_LIB})
                IF(EXISTS ${SD}/${SL})
                  GET_FILENAME_COMPONENT(SL_WE ${SL} NAME_WE)
                  FOREACH(CFG ${CMAKE_CONFIGURATION_TYPES})
                      FILE(COPY        ${SD}/${SL_WE}.dll
                           DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CFG})
                  ENDFOREACH()
                ENDIF()
              ENDFOREACH()
            ENDFOREACH()
        ENDIF()

        SET(testall_output  curv2d_colmajor.silo
                            curv3d.silo
                            curv3d_colmajor.silo
                            poly3d.silo
                            rect2d.silo
                            rect3d.silo
                            ucd2d.silo
                            ucd3d.silo)
        ADD_CUSTOM_COMMAND(OUTPUT  ${testall_output}
                           COMMAND "$<TARGET_FILE:testall>"
                           DEPENDS testall
                           WORKING_DIRECTORY ${DATA_OUT_DIR}
                           COMMENT "Running testall")
        set(globe_output globe.silo globe_mat0.silo)
        ADD_CUSTOM_COMMAND(OUTPUT  ${globe_output}
                           COMMAND "$<TARGET_FILE:globe>"
                           DEPENDS globe
                           WORKING_DIRECTORY ${DATA_OUT_DIR}
                           COMMENT "Running globe")
        set(correlationtest_output dbA00.pdb dbB00.pdb dbC00.pdb)
        ADD_CUSTOM_COMMAND(OUTPUT  ${correlationtest_output}
                           COMMAND "$<TARGET_FILE:correlationtest>"
                           DEPENDS correlationtest
                           WORKING_DIRECTORY ${DATA_OUT_DIR}
                           COMMENT "Running correlationtest")
        set(multi_test_output  multi_curv2d.silo
                               multi_curv3d.silo
                               multi_point2d.silo
                               multi_rect2d.silo
                               multi_rect3d.silo
                               multi_ucd3d.silo
                               hist_ucd3d_0000
                               hist_ucd3d_0001
                               hist_ucd3d_0002
                               hist_ucd3d_0003
                               hist_ucd3d_0004
                               hist_ucd3d_0005
                               hist_ucd3d_0006
                               hist_ucd3d_0007
                               hist_ucd3d_0008
                               hist_ucd3d_0009
                               histne_ucd3d_0000
                               histne_ucd3d_0001
                               histne_ucd3d_0002
                               histne_ucd3d_0003
                               histne_ucd3d_0004
                               histne_ucd3d_0005
                               histne_ucd3d_0006
                               histne_ucd3d_0007
                               histne_ucd3d_0008
                               histne_ucd3d_0009
                               multi_ucd3d_ti_0001
                               multi_ucd3d_ti_0002
                               multi_ucd3d_ti_0003
                               multi_ucd3d_ti_base)
        ADD_CUSTOM_COMMAND(OUTPUT  ${multi_test_output}
                           COMMAND "$<TARGET_FILE:multi_test>"
                           DEPENDS multi_test
                           WORKING_DIRECTORY ${DATA_OUT_DIR}
                           COMMENT "Running multi_test")
        ADD_CUSTOM_COMMAND(OUTPUT  noise.silo
                           COMMAND "$<TARGET_FILE:noise>"
                           DEPENDS noise
                           WORKING_DIRECTORY ${DATA_OUT_DIR}
                           COMMENT "Running noise")
        ADD_CUSTOM_COMMAND(OUTPUT  tire.silo
                           COMMAND "$<TARGET_FILE:tire>"
                           DEPENDS tire
                           WORKING_DIRECTORY ${DATA_OUT_DIR}
                           COMMENT "Running tire")

        ADD_CUSTOM_TARGET(create_data_examples ALL
                          DEPENDS noise.silo
                                  tire.silo
                                  ${globe_output}
                                  ${correlationtest_output}
                                  ${multi_test_output}
                                  ${testall_output}
                         )

        INSTALL(FILES
                    ${DATA_OUT_DIR}/curv2d.silo
                    ${DATA_OUT_DIR}/curv3d.silo
                    ${DATA_OUT_DIR}/dbA00.pdb
                    ${DATA_OUT_DIR}/dbB00.pdb
                    ${DATA_OUT_DIR}/globe.silo
                    ${DATA_OUT_DIR}/globe_mat0.silo
                    ${DATA_OUT_DIR}/multi_rect2d.silo
                    ${DATA_OUT_DIR}/multi_rect3d.silo
                    ${DATA_OUT_DIR}/multi_ucd3d.silo
                    ${DATA_OUT_DIR}/noise.silo
                    ${DATA_OUT_DIR}/poly3d.silo
                    ${DATA_OUT_DIR}/rect2d.silo
                    ${DATA_OUT_DIR}/rect3d.silo
                    ${DATA_OUT_DIR}/tire.silo
                    ${DATA_OUT_DIR}/ucd2d.silo
                    ${DATA_OUT_DIR}/ucd3d.silo
                DESTINATION
                    data
                PERMISSIONS
                    OWNER_READ OWNER_WRITE
                    GROUP_READ GROUP_WRITE
                    WORLD_READ)
    ELSE(SILO_FOUND)
        MESSAGE(STATUS "Data files not included since visit_dist_data.tar.gz")
        MESSAGE(STATUS "is missing and VisIt is not being built with Silo")
        MESSAGE(STATUS "support.")
    ENDIF(SILO_FOUND)
ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/visit_dist_data.tar.gz)


