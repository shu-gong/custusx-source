
if(BUILD_TESTING)
    set(CX_TEST_CATCH_ORG_CUSTUSX_NODE_MOC_SOURCE_FILES
    )
    set(CX_TEST_CATCH_ORG_CUSTUSX_NODE_SOURCE_FILES
        ${CX_TEST_CATCH_ORG_CUSTUSX_NODE_MOC_SOURCE_FILES}
        cxtestNodePlugin.cpp
        cxtestExportDummyClassForLinkingOnWindowsInLibWithoutExportedClass.cpp
    )

    qt5_wrap_cpp(CX_TEST_CATCH_ORG_CUSTUSX_NODE_MOC_SOURCE_FILES ${CX_TEST_CATCH_ORG_CUSTUSX_NODE_MOC_SOURCE_FILES})
    add_library(cxtest_org_custusx_node ${CX_TEST_CATCH_ORG_CUSTUSX_NODE_SOURCE_FILES} ${CX_TEST_CATCH_ORG_CUSTUSX_NODE_MOC_SOURCE_FILES})
    include(GenerateExportHeader)
    generate_export_header(cxtest_org_custusx_node)
    target_include_directories(cxtest_org_custusx_node
        PUBLIC
        .
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    target_link_libraries(cxtest_org_custusx_node
      PRIVATE
      org_custusx_node
      cxCatch
      cxtestUtilities
      cxResource)
    cx_add_tests_to_catch(cxtest_org_custusx_node)

endif(BUILD_TESTING)
