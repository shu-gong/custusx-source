project(org_custusx_example)

set(PLUGIN_export_directive "${PROJECT_NAME}_EXPORT")
cx_initialize_opencv()
set(PLUGIN_SRCS
  cxExamplePluginActivator.cpp
  cxExampleGUIExtenderService.cpp
  cxExampleWidget.cpp
)

# Files which should be processed by Qts moc
set(PLUGIN_MOC_SRCS
  cxExamplePluginActivator.h
  cxExampleGUIExtenderService.h
  cxExampleWidget.h
)

# Qt Designer files which should be processed by Qts uic
set(PLUGIN_UI_FORMS
)

# QRC Files which should be compiled into the plugin
set(PLUGIN_resources
)


#Compute the plugin dependencies
ctkFunctionGetTargetLibraries(PLUGIN_target_libraries)
set(PLUGIN_target_libraries 
    ${PLUGIN_target_libraries}
        #cxResource
    cxGUIExtenderService
    #cxLogicManager
    cxPluginUtilities
	Qt5::Widgets
        #cxGrabber
        ${OpenCV_LIBS}
    )

set(PLUGIN_OUTPUT_DIR "")
if(CX_WINDOWS)
    #on windows we want dlls to be placed with the executables
    set(PLUGIN_OUTPUT_DIR "../")
endif(CX_WINDOWS)

ctkMacroBuildPlugin(
  NAME ${PROJECT_NAME}
  EXPORT_DIRECTIVE ${PLUGIN_export_directive}
  SRCS ${PLUGIN_SRCS} ${PLUGIN_MOC_SRCS}
  MOC_SRCS ${PLUGIN_MOC_SRCS}
  UI_FORMS ${PLUGIN_UI_FORMS}
  RESOURCES ${PLUGIN_resources}
  TARGET_LIBRARIES ${PLUGIN_target_libraries}
  OUTPUT_DIR ${PLUGIN_OUTPUT_DIR}
  ${CX_CTK_PLUGIN_NO_INSTALL}
)

target_include_directories(org_custusx_example
    PUBLIC
    .
    ${CMAKE_CURRENT_BINARY_DIR}
)


add_subdirectory(testing)

