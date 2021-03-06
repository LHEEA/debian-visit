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
#   Brad Whitlock, Wed Aug 24 13:11:30 PDT 2011
#   Add vtkTexturedPointsPainter and remove some obsolete files.
#
#   Brad Whitlock, Wed Oct 12 22:42:12 PDT 2011
#   I moved some mappers to a different library since they may contain Qt. I
#   also cleaned up obsolete stuff in this file.
#
#   Carson Brownlee, Sun May  6 16:25:28 PDT 2012
#   Add support for Manta.
#
#   Kathleen Biagas, Tue Jul 31 12:08:32 MST 2012
#   Change CONFIGURE_FILE settings so things work correctly with 
#   out-of-source builds.
#
#   Kathleen Biagas, Tue Sep  3 11:08:03 PDT 2013
#   Swap avtGLEWInitializer for avtOpenGLExtensionManager.
#
#   Kathleen Biagas, Wed Jan  8 14:19:28 PST 2014
#   Add vtkAxesActor2D.
#
#   Kathleen Biagas, Tue Mar 15 08:26:33 MST 2016
#   OSPRay is only required if requested (VISIT_OSPRAY is set to true/on).
#   Change OSPRay messages type to STATUS.
#
#****************************************************************************/

if(VISIT_OSPRAY)
   SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
       ${VISIT_SOURCE_DIR}/avt/Plotter/OSPRay/CMake)
   FIND_PACKAGE(OSPRay REQUIRED)
endif()

SET(VISIT_VTK_MANTA_SOURCES
Manta/vtkMantaPolyDataMapper.C 
Manta/vtkMantaTexture.C
Manta/vtkMantaProperty.C 
Manta/vtkMantaActor.C 
Manta/vtkMantaCamera.C 
Manta/vtkMantaLight.C 
Manta/vtkMantaDataSetMapper.C
Manta/vtkMantaObjectFactory.C 
Manta/vtkMantaRenderer.C 
Manta/vtkMantaManager.C
Manta/vtkMantaCubeAxesActor.C
)

SET(VISIT_VTK_OSPRAY_SOURCES
    OSPRay/vtkOSPRay/vtkOSPRay.h
    OSPRay/vtkOSPRay/vtkOSPRayActor.cxx
    OSPRay/vtkOSPRay/vtkOSPRayCamera.cxx
    OSPRay/vtkOSPRay/vtkOSPRayLight.cxx
    OSPRay/vtkOSPRay/vtkOSPRayManager.cxx
    OSPRay/vtkOSPRay/vtkOSPRayObjectFactory.cxx
    OSPRay/vtkOSPRay/vtkOSPRayObjectFactory.h
    OSPRay/vtkOSPRay/vtkOSPRayPolyDataMapper.cxx
    OSPRay/vtkOSPRay/vtkOSPRayProperty.cxx
    OSPRay/vtkOSPRay/vtkOSPRayRenderer.cxx
    OSPRay/vtkOSPRay/vtkOSPRayTexture.cxx
    OSPRay/vtkOSPRay/vtkOSPRayVolumeRayCastMapper.h
    OSPRay/vtkOSPRay/vtkOSPRayVolumeRayCastMapper.cxx
    OSPRay/vtkOSPRayModule.h
)

# create configuration file to pass off cmake options
CONFIGURE_FILE(
  "${VISIT_SOURCE_DIR}/avt/Plotter/vtk/InitVTKRenderingConfig.h.in"
  "${VISIT_BINARY_DIR}/include/vtk/InitVTKRenderingConfig.h"
)

SET(AVTPLOTTER_OPENGL_SOURCES
avtOpenGLExtensionManager.C 
avtOpenGLSurfaceAndWireframeRenderer.C 
vtk/vtkOpenGLRectilinearGridMapper.C 
vtk/vtkOpenGLStructuredGridMapper.C 
vtk/vtkOpenGLTexturedBackgroundMapper.C 
vtk/vtkTexturedPointsPainter.C
)

IF(VISIT_USE_GLEW)
    SET(GRAPHICS_INCLUDES ${GLEW_INCLUDE_DIR})
ELSE(VISIT_USE_GLEW)
    SET(GRAPHICS_INCLUDES ${OPENGL_INCLUDE_DIR})
ENDIF(VISIT_USE_GLEW)

SET(AVTPLOTTER_VTK_SOURCES
vtk/InitVTKRendering.C 
vtk/vtkAxesActor2D.C 
vtk/vtkBackgroundActor.C 
vtk/vtkLineLegend.C 
vtk/vtkMultiFontVectorText.C 
vtk/vtkParallelImageSpaceRedistributor.C 
vtk/vtkRectilinearGridMapper.C 
vtk/vtkStructuredGridMapper.C 
vtk/vtkTexturedBackgroundActor.C 
vtk/vtkTimeSliderActor.C 
vtk/vtkTriad2D.C 
vtk/vtkVectorFontCharacterData.C 
vtk/vtkVisItAxisActor.C 
vtk/vtkVisItAxisActor2D.C 
vtk/vtkVisItCubeAxesActor.C 
vtk/vtkVisItDataSetMapper.C 
vtk/vtkVisItScalarBarActor.C 
vtk/vtkVisItScalarBarWithOpacityActor.C 
vtk/vtkVisItTextActor.C
)

SET(AVTPLOTTER_SOURCES
avtActor.C
avtBehavior.C
avtCurveLegend.C
avtCustomRenderer.C
avtDecorationsDrawable.C
avtDecorationsMapper.C
avtDrawable.C
avtDrawer.C
avtExternallyRenderedImagesActor.C
avtGeometryDrawable.C
avtImageDrawable.C
avtImageMapper.C
avtLabelActor.C
avtLabeledCurveMapper.C
avtLegend.C
avtLevelsLegend.C
avtLevelsMapper.C
avtLevelsPointGlyphMapper.C
avtLightList.C
avtLineoutActor.C
avtMapper.C
avtPickActor.C
avtPlot.C
avtPlotMetaData.C
avtPointGlypher.C
avtSoftwareShader.C
avtSurfaceAndWireframeRenderer.C
avtTensorGlyphMapper.C
avtTheater.C
avtTransparencyActor.C
avtUserDefinedMapper.C
avtVariableLegend.C
avtVariableMapper.C
avtVariablePointGlyphMapper.C
avtVectorGlyphMapper.C
avtVolumeVariableLegend.C
RenderOrder.C
${AVTPLOTTER_VTK_SOURCES}
${AVTPLOTTER_OPENGL_SOURCES}
)

IF(VISIT_MANTA)
  SET(AVTPLOTTER_SOURCES ${AVTPLOTTER_SOURCES} ${VISIT_VTK_MANTA_SOURCES} )
ENDIF(VISIT_MANTA)

IF(VISIT_OSPRAY)
    SET(AVTPLOTTER_SOURCES ${AVTPLOTTER_SOURCES} ${VISIT_VTK_OSPRAY_SOURCES} )
    SET(VTK_INCLUDE_DIRS ${VTK_INCLUDE_DIRS}
        ${VISIT_SOURCE_DIR}/../../VTK-6.1.0/Rendering/Volume)
ENDIF(VISIT_OSPRAY)

INCLUDE_DIRECTORIES(
${VISIT_COMMON_INCLUDES}
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/vtk
${VISIT_SOURCE_DIR}/avt/DBAtts/MetaData
${VISIT_SOURCE_DIR}/avt/DBAtts/SIL
${VISIT_SOURCE_DIR}/avt/Database/Database
${VISIT_SOURCE_DIR}/avt/Filters
${VISIT_SOURCE_DIR}/avt/Math
${VISIT_SOURCE_DIR}/avt/VisWindow/VisWindow
${VISIT_SOURCE_DIR}/avt/Pipeline/AbstractFilters
${VISIT_SOURCE_DIR}/avt/Pipeline/Data
${VISIT_SOURCE_DIR}/avt/Pipeline/Pipeline
${VISIT_SOURCE_DIR}/avt/Pipeline/Sinks
${VISIT_SOURCE_DIR}/avt/Pipeline/Sources
${VISIT_SOURCE_DIR}/avt/Plotter/Manta
${VISIT_SOURCE_DIR}/avt/Plotter/OSPRay
${VISIT_SOURCE_DIR}/avt/Plotter/OSPRay/vtkOSPRay
${VISIT_SOURCE_DIR}/avt/View
${VISIT_SOURCE_DIR}/visit_vtk/full
${VISIT_SOURCE_DIR}/visit_vtk/lightweight
${PROJECT_BINARY_DIR}/avt/Plotter/vtk/
${VTK_INCLUDE_DIRS}
${GRAPHICS_INCLUDES}
)

# Add link directories
LINK_DIRECTORIES(${LIBRARY_OUTPUT_DIRECTORY} ${EAVL_LIBRARY_DIR} ${VTK_LIBRARY_DIRS} ${MESA_LIBRARY_DIR} ${GLEW_LIBRARY_DIR} )


#********************************* SERIAL ************************************
ADD_LIBRARY(avtplotter_ser ${AVTPLOTTER_SOURCES})
IF(HAVE_LIB_R)
    TARGET_LINK_LIBRARIES(avtplotter_ser visitcommon avtmath avtview avtfilters_ser avtpipeline_ser visit_vtk lightweight_visit_vtk vtkFiltersHybrid vtkRenderingCore vtkRenderingFreeType vtkRenderingFreeTypeOpenGL ${GLEW_LIB} vtkFiltersStatisticsGnuR)
ELSE(HAVE_LIB_R)
    TARGET_LINK_LIBRARIES(avtplotter_ser visitcommon avtmath avtview avtfilters_ser avtpipeline_ser visit_vtk lightweight_visit_vtk vtkFiltersHybrid vtkRenderingCore vtkRenderingFreeType vtkRenderingFreeTypeOpenGL ${GLEW_LIB})
ENDIF(HAVE_LIB_R)
# Add vtk defines
ADD_TARGET_DEFINITIONS(avtplotter_ser "${VTK_DEFINITIONS}")
IF(VISIT_MANTA)
  TARGET_LINK_LIBRARIES(avtplotter_ser ${MANTA_TARGET_LINK_LIBRARIES})
ENDIF(VISIT_MANTA)
IF(VISIT_OSPRAY)
    MESSAGE(STATUS "OSPRAY_TARGET_LINK_LIBRARIES: " ${OSPRAY_TARGET_LINK_LIBRARIES})
    MESSAGE(STATUS "OSPRAY_LIBRARIES: " ${OSPRAY_LIBRARIES})
    MESSAGE(STATUS "OSPRAY_INCLUDE_DIRS: " ${OSPRAY_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(avtplotter_ser ${OSPRAY_TARGET_LINK_LIBRARIES}
        ${OSPRAY_LIBRARIES} ${VTK_LIBRARIES})
    INCLUDE_DIRECTORIES(${OSPRAY_INCLUDE_DIRS} ${VISIT_SOURCE_DIR}/../../VTK-6.1.0/Parallel/Core)
ENDIF(VISIT_OSPRAY)
VISIT_INSTALL_TARGETS(avtplotter_ser)

#********************************* PARALLEL **********************************
IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(avtplotter_par ${AVTPLOTTER_SOURCES})
    IF(HAVE_LIB_R)
        TARGET_LINK_LIBRARIES(avtplotter_par visitcommon avtmath avtview avtfilters_par avtpipeline_par visit_vtk lightweight_visit_vtk vtkFiltersHybrid vtkRenderingCore vtkRenderingFreeType vtkRenderingFreeTypeOpenGL ${GLEW_LIB} vtkFiltersStatisticsGnuR)
    ELSE(HAVE_LIB_R)
        TARGET_LINK_LIBRARIES(avtplotter_par visitcommon avtmath avtview avtfilters_par avtpipeline_par visit_vtk lightweight_visit_vtk vtkFiltersHybrid vtkRenderingCore vtkRenderingFreeType vtkRenderingFreeTypeOpenGL ${GLEW_LIB})
    ENDIF(HAVE_LIB_R)
    # Add vtk defines
    ADD_TARGET_DEFINITIONS(avtplotter_par "${VTK_DEFINITIONS}")
    IF(VISIT_MANTA)
      TARGET_LINK_LIBRARIES(avtplotter_par ${MANTA_TARGET_LINK_LIBRARIES})
      #IF(ICET_FOUND)
      #  INCLUDE_DIRECTORIES(${ICET_INCLUDE_DIR})
      #  LINK_DIRECTORIES(${ICET_LIBRARY_DIR})
      #ENDIF(ICET_FOUND)
    ENDIF(VISIT_MANTA)
    IF(VISIT_OSPRAY)
        TARGET_LINK_LIBRARIES(avtplotter_par ${OSPRAY_TARGET_LINK_LIBRARIES}
            ${OSPRAY_LIBRARIES})
    ENDIF(VISIT_OSPRAY)

    VISIT_INSTALL_TARGETS(avtplotter_par)
ENDIF(VISIT_PARALLEL)


