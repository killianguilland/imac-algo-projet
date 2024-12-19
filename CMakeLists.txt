cmake_minimum_required(VERSION 3.20)
include(FetchContent)

# You can set the name of your project here
project(TicTacToe)
add_executable(${PROJECT_NAME})

# Choose your C++ version
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Prevents compiler-specific extensions to C++ because they might allow code to compile on your machine but not on other people's machine
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF)

# Add all the source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src lib)

FetchContent_Declare(
    terminal_ctrl
    GIT_REPOSITORY https://github.com/dsmtE/terminal_ctrl
    GIT_TAG "origin/main"
)


find_package(raylib REQUIRED)

FetchContent_MakeAvailable(terminal_ctrl)
target_link_libraries(${PROJECT_NAME} PRIVATE terminal_ctrl raylib)

# (Optional) Include Raylib headers for IDEs
target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_INCLUDE_DIRS})