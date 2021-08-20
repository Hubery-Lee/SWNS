cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
set(PROJ_NAME SWNS)
project(${PROJ_NAME})
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})  #设置程序安装目录

add_subdirectory(code_gui)
