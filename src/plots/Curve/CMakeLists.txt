# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(Curve_plot)

INCLUDE(${VISIT_SOURCE_DIR}/CMake/PluginMacros.cmake)

SET(COMMON_SOURCES
CurvePluginInfo.C
CurveCommonPluginInfo.C
CurveAttributes.C
)

SET(LIBI_SOURCES 
CurvePluginInfo.C
)

SET(LIBG_SOURCES
CurveGUIPluginInfo.C
QvisCurvePlotWindow.C
${COMMON_SOURCES}
)
SET(LIBG_MOC_SOURCES
QvisCurvePlotWindow.h
)

SET(LIBV_SOURCES
CurveViewerEnginePluginInfo.C
CurveViewerPluginInfo.C
avtCurvePlot.C
avtCurveFilter.C
avtCurveRenderer.C
avtOpenGLCurveRenderer.C
avtPolarToCartesianFilter.C
${COMMON_SOURCES}
)

SET(LIBE_SOURCES
CurveViewerEnginePluginInfo.C
CurveEnginePluginInfo.C
avtCurvePlot.C
avtCurveFilter.C
avtCurveRenderer.C
avtOpenGLCurveRenderer.C
avtPolarToCartesianFilter.C
${COMMON_SOURCES}
)

IF (NOT WIN32)
    SET_SOURCE_FILES_PROPERTIES(avtOpenGLCurveRenderer.C 
        PROPERTIES
        COMPILE_FLAGS "-I ${OPENGL_INCLUDE_DIR}"
    )
ENDIF (NOT WIN32)

IF(VISIT_PYTHON_SCRIPTING)
    SET(PYINCLUDES ${PYTHON_INCLUDE_PATH} ${VISIT_INCLUDE_DIR}/visitpy/visitpy)
ENDIF(VISIT_PYTHON_SCRIPTING)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_COMMON_INCLUDES}
${VISIT_INCLUDE_DIR}/avt/DBAtts/MetaData
${VISIT_INCLUDE_DIR}/avt/DBAtts/SIL
${VISIT_INCLUDE_DIR}/avt/Database/Database
${VISIT_INCLUDE_DIR}/avt/FileWriter
${VISIT_INCLUDE_DIR}/avt/Filters
${VISIT_INCLUDE_DIR}/avt/IVP
${VISIT_INCLUDE_DIR}/avt/Math
${VISIT_INCLUDE_DIR}/avt/Pipeline/AbstractFilters
${VISIT_INCLUDE_DIR}/avt/Pipeline/Data
${VISIT_INCLUDE_DIR}/avt/Pipeline/Pipeline
${VISIT_INCLUDE_DIR}/avt/Pipeline/Sinks
${VISIT_INCLUDE_DIR}/avt/Pipeline/Sources
${VISIT_INCLUDE_DIR}/avt/Plotter
${VISIT_INCLUDE_DIR}/avt/QtVisWindow
${VISIT_INCLUDE_DIR}/avt/View
${VISIT_INCLUDE_DIR}/avt/VisWindow/Colleagues
${VISIT_INCLUDE_DIR}/avt/VisWindow/Interactors
${VISIT_INCLUDE_DIR}/avt/VisWindow/Proxies
${VISIT_INCLUDE_DIR}/avt/VisWindow/Tools
${VISIT_INCLUDE_DIR}/avt/VisWindow/VisWindow
${VISIT_INCLUDE_DIR}/gui
${VISIT_INCLUDE_DIR}/viewer/core
${VISIT_INCLUDE_DIR}/viewer/main
${VISIT_INCLUDE_DIR}/viewer/main/ui
${VISIT_INCLUDE_DIR}/viewer/proxy
${VISIT_INCLUDE_DIR}/viewer/rpc
${VISIT_INCLUDE_DIR}/winutil
${VISIT_INCLUDE_DIR}/visit_vtk/full
${VISIT_INCLUDE_DIR}/visit_vtk/lightweight
${QT_INCLUDE_DIR}
${QT_QTCORE_INCLUDE_DIR}
${QT_QTGUI_INCLUDE_DIR}
${EAVL_INCLUDE_DIR}
${VTKM_INCLUDE_DIR}
${VTK_INCLUDE_DIRS}
${PYINCLUDES}
${GLEW_INCLUDE_DIR}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} ${QT_LIBRARY_DIR} ${QWT_LIBRARY_DIR} ${GLEW_LIBRARY_DIR} ${EAVL_LIBRARY_DIR} ${VTKM_LIBRARY_DIR} ${VTK_LIBRARY_DIRS} )

ADD_LIBRARY(ICurvePlot ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(ICurvePlot visitcommon)
SET(INSTALLTARGETS ICurvePlot)

IF(NOT VISIT_SERVER_COMPONENTS_ONLY AND NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    QT_WRAP_CPP(GCurvePlot LIBG_SOURCES ${LIBG_MOC_SOURCES})
    ADD_LIBRARY(GCurvePlot ${LIBG_SOURCES})
    TARGET_LINK_LIBRARIES(GCurvePlot visitcommon gui )

    ADD_LIBRARY(VCurvePlot ${LIBV_SOURCES})
    TARGET_LINK_LIBRARIES(VCurvePlot visitcommon viewer )

    SET(INSTALLTARGETS ${INSTALLTARGETS} GCurvePlot VCurvePlot)

    IF(VISIT_PYTHON_SCRIPTING)
        SET(LIBS_SOURCES
            CurveScriptingPluginInfo.C
            PyCurveAttributes.C
            ${COMMON_SOURCES}
        )
        ADD_LIBRARY(SCurvePlot ${LIBS_SOURCES})
        TARGET_LINK_LIBRARIES(SCurvePlot visitcommon visitpy ${PYTHON_LIBRARY})
        SET(INSTALLTARGETS ${INSTALLTARGETS} SCurvePlot)
    ENDIF(VISIT_PYTHON_SCRIPTING)

    IF(VISIT_JAVA)
        FILE(COPY CurveAttributes.java DESTINATION ${JavaClient_BINARY_DIR}/src/plots)
        ADD_CUSTOM_TARGET(JavaCurve ALL ${Java_JAVAC_EXECUTABLE} ${VISIT_Java_FLAGS} -d ${JavaClient_BINARY_DIR} -classpath ${JavaClient_BINARY_DIR} -sourcepath ${JavaClient_BINARY_DIR} CurveAttributes.java
            DEPENDS JavaClient
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    ENDIF(VISIT_JAVA)
ENDIF(NOT VISIT_SERVER_COMPONENTS_ONLY AND NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(ECurvePlot_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(ECurvePlot_ser visitcommon avtplotter_ser avtpipeline_ser )
SET(INSTALLTARGETS ${INSTALLTARGETS} ECurvePlot_ser)
ADD_TARGET_DEFINITIONS(ECurvePlot_ser ENGINE)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(ECurvePlot_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(ECurvePlot_par visitcommon avtplotter_par avtpipeline_par )
    SET(INSTALLTARGETS ${INSTALLTARGETS} ECurvePlot_par)
    ADD_TARGET_DEFINITIONS(ECurvePlot_par ENGINE)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_PLOT_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(plots ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(plots Curve ${INSTALLTARGETS})

