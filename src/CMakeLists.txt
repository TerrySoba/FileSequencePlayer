project(FileSequencePlayer)

add_library(${PROJECT_NAME}Lib
    main_window.h
    main_window.cpp
    main_window_controller.h
    main_window_controller.cpp
    file_sequence_finder.h
    file_sequence_finder.cpp
    file_sequence_finder_boost.h
    file_sequence_finder_boost.cpp)

target_link_libraries(${PROJECT_NAME}Lib
    Qt5::Widgets
    Boost::filesystem)

add_executable(${PROJECT_NAME}
    main.cpp)


target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}Lib)



set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doxygen)

configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_custom_target(doxygen
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIR}
    COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
