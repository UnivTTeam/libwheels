cmake_minimum_required(VERSION 3.0)
project(test CXX)

add_compile_definitions(LibraryTest)

file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
foreach (TARGET_SOURCE ${SOURCES})
    get_filename_component(TARGET_SOURCE_NAME ${TARGET_SOURCE} NAME_WE)
    message("[target] ${TARGET_SOURCE_NAME}")
    add_executable(${TARGET_SOURCE_NAME} ${TARGET_SOURCE})
    target_include_directories(${TARGET_SOURCE_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../
    )
endforeach ()

