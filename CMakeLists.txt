cmake_minimum_required(VERSION 3.27)
project(c-daw C)
set(CMAKE_C_STANDARD 99)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5"
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

set(ENGINE_SRC
    engine/engine.c
)

set(COMPONENTS_SRC
    components/cButtons.c
)

set(LAYOUTS_SRC
    layouts/layoutEditor.c
)

add_executable(c-daw 
    main.c
    headers/globals.c
    ${ENGINE_SRC}
    ${COMPONENTS_SRC}
    ${LAYOUTS_SRC}
)

target_compile_options(c-daw PUBLIC)
target_include_directories(c-daw PUBLIC .)

target_link_libraries(c-daw PUBLIC raylib)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

add_custom_command(
        TARGET c-daw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources)
