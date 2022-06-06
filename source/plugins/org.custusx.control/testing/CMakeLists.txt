
if(BUILD_TESTING)
    set(CX_TEST_CATCH_ORG_CUSTUSX_CONTROL_MOC_SOURCE_FILES
    )
    set(CX_TEST_CATCH_ORG_CUSTUSX_CONTROL_SOURCE_FILES
        ${CX_TEST_CATCH_ORG_CUSTUSX_CONTROL_MOC_SOURCE_FILES}
        cxtestControlPlugin.cpp
        cxtestExportDummyClassForLinkingOnWindowsInLibWithoutExportedClass.cpp
    )

    qt5_wrap_cpp(CX_TEST_CATCH_ORG_CUSTUSX_CONTROL_MOC_SOURCE_FILES ${CX_TEST_CATCH_ORG_CUSTUSX_CONTROL_MOC_SOURCE_FILES})
    add_library(cxtest_org_custusx_control ${CX_TEST_CATCH_ORG_CUSTUSX_CONTROL_SOURCE_FILES} ${CX_TEST_CATCH_ORG_CUSTUSX_CONTROL_MOC_SOURCE_FILES})
    include(GenerateExportHeader)
    generate_export_header(cxtest_org_custusx_control)
    target_include_directories(cxtest_org_custusx_control
        PUBLIC
        .
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    target_link_libraries(cxtest_org_custusx_control
      PRIVATE
      org_custusx_control
      cxCatch
      cxtestUtilities
      cxResource)
    cx_add_tests_to_catch(cxtest_org_custusx_control)

endif(BUILD_TESTING)
