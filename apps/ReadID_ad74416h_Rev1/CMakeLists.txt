# Minimum CMake version
cmake_minimum_required(VERSION 3.20.0)

# Add additional modules 
set(ZEPHYR_EXTRA_MODULES "${CMAKE_SOURCE_DIR}/../../modules/ad74416h")

# Locate the Zephyr RTOS source 
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Name the project
project(ReadID_ad74416h_Rev1)

# Locate the source code for the application
target_sources(app PRIVATE src/main.c)