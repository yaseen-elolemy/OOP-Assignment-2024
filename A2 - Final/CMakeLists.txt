# Set minimum required CMake version and project details
cmake_minimum_required(VERSION 3.29)
project(A2)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Include directories for Dear ImGui and GLFW
include_directories(
        ${CMAKE_SOURCE_DIR}             # Includes ImGui files in the working directory
                   # Includes GLFW headers
)

# GLFW Library paths

# Add source files for Dear ImGui

# Add the executable target
add_executable(${PROJECT_NAME} main.cpp ${IMGUI_SOURCES}
        ultimate.h
        games.h)

# Link GLFW and OpenGL libraries
target_link_libraries(${PROJECT_NAME}
       )
