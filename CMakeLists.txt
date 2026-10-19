cmake_minimum_required(VERSION 3.10)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_LIST_DIR)
    project(websocket-accept LANGUAGES C)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS ON)

    if(MSVC)
        add_compile_options(/Wall)
    else()
        add_compile_options(-Wall)
    endif()
endif()

set(ws_src
    ${CMAKE_CURRENT_LIST_DIR}/websocket-accept.c
    ${CMAKE_CURRENT_LIST_DIR}/sha1/sha1.c
)
add_library(websocket_accept STATIC ${ws_src})
target_include_directories(websocket_accept PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if(MSVC)
else()
    target_compile_options(websocket_accept PRIVATE -Wextra -Wshadow)
endif()

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_LIST_DIR)
    add_executable(test ${CMAKE_CURRENT_LIST_DIR}/test.c)
    target_link_libraries(test PRIVATE websocket_accept)
endif()
