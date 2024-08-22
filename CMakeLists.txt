cmake_minimum_required(VERSION 3.10)

# Project Name
project(ArbNet)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the path to your Qt installation (already set via Homebrew)
set(Qt5_DIR "/opt/homebrew/opt/qt/lib/cmake/Qt5")

# Find Qt5 package
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/StrategyExamples)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories("/opt/homebrew/opt/qt/include")

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link with Qt libraries
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
