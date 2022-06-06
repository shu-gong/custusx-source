project(org_custusx_planning)

set(PLUGIN_export_directive "${PROJECT_NAME}_EXPORT")

set(PLUGIN_SRCS
  cxPlanningPluginActivator.cpp
  cxPlanningGUIExtenderService.cpp
  cxPlanningWidget.cpp

  include/macros/class_forward.h

  include/planner/InsertPlanner.hpp
  include/planner/Planner.hpp
  include/planner/RRT.hpp
  include/planner/Tree.hpp

  include/StateSpace/insertSpace.hpp
  include/StateSpace/rn.hpp
  include/StateSpace/SE3.hpp
  include/StateSpace/SO3.hpp
  include/StateSpace/StateSpace.hpp
)

# Files which should be processed by Qts moc
set(PLUGIN_MOC_SRCS
  cxPlanningPluginActivator.h
  cxPlanningGUIExtenderService.h
  cxPlanningWidget.h
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
    cxResource
    cxResourceWidgets
    cxPluginUtilities
    cxGUIExtenderService
    cxGui
    cxResourceVisualization
    cxLogicManager
    #cxLogicManager
        Qt5::Widgets
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

target_include_directories(org_custusx_planning
    PUBLIC
    .
    ./include/macros
    ./include/planner
    ./include/StateSpace
    ${CMAKE_CURRENT_BINARY_DIR}
)


# add_subdirectory(testing)

