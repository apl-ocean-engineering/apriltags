<<<<<<< HEAD
include_directories( ${CONAN_INCLUDE_DIRS}
=======

include_directories( ${GTEST_INCLUDE_DIRS}
                     ${CONAN_INCLUDE_DIRS}
>>>>>>> ae0dfeff2af877559d7f3fa1b83a3c593f853a5d
                     ${CMAKE_SOURCE_DIR}/test/data )

set( UNIT_TEST_FILES
    corner_detector_test.cc
    corners_test.cc
    tag_array_test.cc )
    # subtag_detector_test.cc
    # tag_detector_test.cc )

add_executable( apriltags_unit_test
               ${UNIT_TEST_FILES} )

target_link_libraries( apriltags_unit_test
          ${CONAN_LIBS}
          ${OpenCV_LIBS}
          ${CONAN_LIBS}
          apriltags )

# Don't use ctest, instead just exectute the Google test binaries
add_custom_target( unit_test ${CMAKE_CURRENT_BINARY_DIR}/apriltags_unit_test
                    DEPENDS apriltags_unit_test )
