project(org_custusx_vslam)

set(PLUGIN_export_directive "${PROJECT_NAME}_EXPORT")

FILE(GLOB SRC_ORBSLAM2_FILES
        "Thirdparty/ORBSLAM_2/src/*.cc")

FILE(GLOB SRC_DEFSLAM_FILES
        "Modules/Common/*.cc"
        "Modules/GroundTruth/*.cc"
        "Modules/Mapping/*.cc"
        "Modules/Matching/*.cc"
        "Modules/Settings/*.h"
        "Modules/Template/*.cc"
        "Modules/Tracking/*.cc"
        "Modules/Viewer/*.cc")

set(PLUGIN_SRCS
  cxVslamPluginActivator.cpp
  cxVslamGUIExtenderService.cpp
  cxVslamWidget.cpp
        
  # BBS
  Thirdparty/BBS/bbs.cc
  Thirdparty/BBS/bbs_coloc.cc
        
  # DBoW2
  Thirdparty/DBoW2/DBoW2/BowVector.cpp
  Thirdparty/DBoW2/DBoW2/FORB.cpp
  Thirdparty/DBoW2/DBoW2/FeatureVector.cpp
  Thirdparty/DBoW2/DBoW2/ScoringObject.cpp
  Thirdparty/DBoW2/DUtils/Random.cpp
  Thirdparty/DBoW2/DUtils/Timestamp.cpp
        
  #g2o
    Thirdparty/g2o/g2o/types/types_sba.h
    Thirdparty/g2o/g2o/types/types_six_dof_expmap.h
    Thirdparty/g2o/g2o/types/types_sba.cpp
    Thirdparty/g2o/g2o/types/types_six_dof_expmap.cpp
    Thirdparty/g2o/g2o/types/types_seven_dof_expmap.cpp
    Thirdparty/g2o/g2o/types/types_seven_dof_expmap.h
    Thirdparty/g2o/g2o/types/se3quat.h
    Thirdparty/g2o/g2o/types/se3_ops.h
    Thirdparty/g2o/g2o/types/se3_ops.hpp
    #core
    Thirdparty/g2o/g2o/core/base_edge.h
    Thirdparty/g2o/g2o/core/base_binary_edge.h
    Thirdparty/g2o/g2o/core/hyper_graph_action.cpp
    Thirdparty/g2o/g2o/core/base_binary_edge.hpp
    Thirdparty/g2o/g2o/core/hyper_graph_action.h
    Thirdparty/g2o/g2o/core/base_multi_edge.h
    Thirdparty/g2o/g2o/core/hyper_graph.cpp
    Thirdparty/g2o/g2o/core/base_multi_edge.hpp
    Thirdparty/g2o/g2o/core/hyper_graph.h
    Thirdparty/g2o/g2o/core/base_unary_edge.h
    Thirdparty/g2o/g2o/core/linear_solver.h
    Thirdparty/g2o/g2o/core/base_unary_edge.hpp
    Thirdparty/g2o/g2o/core/marginal_covariance_cholesky.cpp
    Thirdparty/g2o/g2o/core/base_vertex.h
    Thirdparty/g2o/g2o/core/marginal_covariance_cholesky.h
    Thirdparty/g2o/g2o/core/base_vertex.hpp
    Thirdparty/g2o/g2o/core/matrix_structure.cpp
    Thirdparty/g2o/g2o/core/batch_stats.cpp
    Thirdparty/g2o/g2o/core/matrix_structure.h
    Thirdparty/g2o/g2o/core/batch_stats.h
    Thirdparty/g2o/g2o/core/openmp_mutex.h
    Thirdparty/g2o/g2o/core/block_solver.h
    Thirdparty/g2o/g2o/core/block_solver.hpp
    Thirdparty/g2o/g2o/core/parameter.cpp
    Thirdparty/g2o/g2o/core/parameter.h
    Thirdparty/g2o/g2o/core/cache.cpp
    Thirdparty/g2o/g2o/core/cache.h
    Thirdparty/g2o/g2o/core/optimizable_graph.cpp
    Thirdparty/g2o/g2o/core/optimizable_graph.h
    Thirdparty/g2o/g2o/core/solver.cpp
    Thirdparty/g2o/g2o/core/solver.h
    Thirdparty/g2o/g2o/core/creators.h
    Thirdparty/g2o/g2o/core/optimization_algorithm_factory.cpp
    Thirdparty/g2o/g2o/core/estimate_propagator.cpp
    Thirdparty/g2o/g2o/core/optimization_algorithm_factory.h
    Thirdparty/g2o/g2o/core/estimate_propagator.h
    Thirdparty/g2o/g2o/core/factory.cpp
    Thirdparty/g2o/g2o/core/optimization_algorithm_property.h
    Thirdparty/g2o/g2o/core/factory.h
    Thirdparty/g2o/g2o/core/sparse_block_matrix.h
    Thirdparty/g2o/g2o/core/sparse_optimizer.cpp
    Thirdparty/g2o/g2o/core/sparse_block_matrix.hpp
    Thirdparty/g2o/g2o/core/sparse_optimizer.h
    Thirdparty/g2o/g2o/core/hyper_dijkstra.cpp
    Thirdparty/g2o/g2o/core/hyper_dijkstra.h
    Thirdparty/g2o/g2o/core/parameter_container.cpp
    Thirdparty/g2o/g2o/core/parameter_container.h
    Thirdparty/g2o/g2o/core/optimization_algorithm.cpp
    Thirdparty/g2o/g2o/core/optimization_algorithm.h
    Thirdparty/g2o/g2o/core/optimization_algorithm_with_hessian.cpp
    Thirdparty/g2o/g2o/core/optimization_algorithm_with_hessian.h
    Thirdparty/g2o/g2o/core/optimization_algorithm_levenberg.cpp
    Thirdparty/g2o/g2o/core/optimization_algorithm_levenberg.h

    Thirdparty/g2o/g2o/core/optimization_algorithm_dogleg.cpp
    Thirdparty/g2o/g2o/core/optimization_algorithm_dogleg.h


    Thirdparty/g2o/g2o/core/jacobian_workspace.cpp
    Thirdparty/g2o/g2o/core/jacobian_workspace.h
    Thirdparty/g2o/g2o/core/robust_kernel.cpp
    Thirdparty/g2o/g2o/core/robust_kernel.h
    Thirdparty/g2o/g2o/core/robust_kernel_factory.cpp
    Thirdparty/g2o/g2o/core/robust_kernel_factory.h
    Thirdparty/g2o/g2o/core/robust_kernel_impl.cpp
    Thirdparty/g2o/g2o/core/robust_kernel_impl.h
    #stuff
    Thirdparty/g2o/g2o/stuff/string_tools.h
    Thirdparty/g2o/g2o/stuff/color_macros.h
    Thirdparty/g2o/g2o/stuff/macros.h
    Thirdparty/g2o/g2o/stuff/timeutil.cpp
    Thirdparty/g2o/g2o/stuff/misc.h
    Thirdparty/g2o/g2o/stuff/timeutil.h
    Thirdparty/g2o/g2o/stuff/os_specific.c
    Thirdparty/g2o/g2o/stuff/os_specific.h
    Thirdparty/g2o/g2o/stuff/string_tools.cpp
    Thirdparty/g2o/g2o/stuff/property.cpp
    Thirdparty/g2o/g2o/stuff/property.h
    #class for DefSLAM for shape-from-template
    Thirdparty/g2o/g2o/types/sft_types.h

    # ORBSLAM_2
    ${SRC_ORBSLAM2_FILES}
    ${SRC_DEFSLAM_FILES}
)

# Files which should be processed by Qts moc
set(PLUGIN_MOC_SRCS
  cxVslamPluginActivator.h
  cxVslamGUIExtenderService.h
  cxVslamWidget.h
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

target_include_directories(org_custusx_vslam
    PUBLIC
    .
    ./Thirdparty/BBS
    ./Thirdparty/DBoW2/DBoW2 
    ./Thirdparty/DBoW2/DUtils
    ./Thirdparty/g2o/g2o/core
    ./Thirdparty/g2o/g2o/types
    ./Thirdparty/g2o/g2o/stuff
    ./Thirdparty/ORBSLAM_2/include
    ./Modules/Common
    ./Modules/GroundTruth
    ./Modules/Mapping
    ./Modules/Matching
    ./Modules/Template
    ./Modules/Tracking
    ./Modules/Settings
    ./Modules/Viewer
    ${CMAKE_CURRENT_BINARY_DIR}
)


# add_subdirectory(testing)

