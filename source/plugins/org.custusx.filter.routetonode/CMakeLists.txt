project(org_custusx_filter_routetonode)

include(cxInstallUtilities)


set(PLUGIN_export_directive "${PROJECT_NAME}_EXPORT")

set(PLUGIN_SRCS
    cxRouteToNode.h
    cxRouteToNode.cpp
    cxFilterRouteToNodePluginActivator.cpp
    cxRouteToNodeFilterService.cpp
    
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
    cxFilterRouteToNodePluginActivator.h
    cxRouteToNodeFilterService.h
)

set(PLUGIN_UI_FORMS
)

# QRC Files which should be compiled into the plugin
set(PLUGIN_resources
)


#Compute the plugin dependencies
ctkFunctionGetTargetLibraries(PLUGIN_target_libraries)
set(PLUGIN_target_libraries
    PUBLIC
    ${PLUGIN_target_libraries}
    #cxPluginAlgorithm

    PRIVATE
    cxResource
    cxResourceFilter
    cxPluginUtilities
    org_custusx_registration_method_bronchoscopy
    org_custusx_filter_airwaysfromcenterline
)

set(PLUGIN_OUTPUT_DIR "")
if(CX_WINDOWS)
    #on windows we want dlls to be placed with the executables
    set(PLUGIN_OUTPUT_DIR "../")
endif(CX_WINDOWS)

ctkMacroBuildPlugin(
  NAME ${PROJECT_NAME}
  EXPORT_DIRECTIVE ${PLUGIN_export_directive}
  SRCS ${PLUGIN_SRCS}
  MOC_SRCS ${PLUGIN_MOC_SRCS}
  UI_FORMS ${PLUGIN_UI_FORMS}
  RESOURCES ${PLUGIN_resources}
  TARGET_LIBRARIES ${PLUGIN_target_libraries}
  OUTPUT_DIR ${PLUGIN_OUTPUT_DIR}
  ${CX_CTK_PLUGIN_NO_INSTALL}
)

target_include_directories(org_custusx_filter_routetonode
    PUBLIC
    .
    ${CMAKE_CURRENT_BINARY_DIR}
)

#cx_doc_define_plugin_user_docs("${PROJECT_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/doc")
#cx_add_non_source_file("doc/org.custusx.filter.routetotarget.md")


