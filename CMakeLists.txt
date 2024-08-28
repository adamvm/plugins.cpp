
cmake_minimum_required(VERSION 3.15)
project(PluginSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(.)

# Create the shared library (plugin)
add_library(myplugin SHARED my_plugin.cpp)

# Create the main application
add_executable(main_app main.cpp)

# Link the application with the dl library for dynamic loading
target_link_libraries(main_app ${CMAKE_DL_LIBS})
