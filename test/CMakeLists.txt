project(FileSequencePlayerTest)

set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/testdata)
configure_file(test_data.h.in ${CMAKE_CURRENT_BINARY_DIR}/test_data.h)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rd_party/catch
    ${CMAKE_SOURCE_DIR}/src)

add_executable(FileSequencePlayerTest
    testmain.cpp
    file_sequence_finder_boost_test.cpp)

target_link_libraries(FileSequencePlayerTest
    FileSequencePlayerLib
    )
