
cmake_minimum_required(VERSION 3.16)
set(PROJ_NAME SWNS-GUI)
project(${PROJ_NAME} LANGUAGES CXX)

# set compiler flags
# c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE "Release")

# 设置程序安装目录
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# instruct cmake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)   # saves having to use QT5_WRAP_CPP
set(CMAKE_AUTORCC ON)   # saves having to use QT5_ADD_RESOURCES
set(CMAKE_AUTOUIC ON)   # saves having to use QT5_WRAP_UI

# find ui files
# set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

#--------------------------------------------------
# find package required
#
find_package(Qt5 COMPONENTS Core REQUIRED) # Core stuff
find_package(Qt5 COMPONENTS Gui REQUIRED) # Gui for openGL integration
# find_package(Qt5 COMPONENTS NetWork REQUIRED) # for network 
# find_package(Qt5 COMPONENTS Concurrent REQUIRED) # for threading
# find_package(Qt5 COMPONENTS Gamepad)  # controller support
# find_package(Qt5 COMPONENTS OpenGLExtensions REQUIRED)  #for openGL
# find_package(Qt5OpenGL)
# find_package(Qt5 COMPONENTS Multimedia REQUIRED) # multimedia capabilities
# find_package(Qt5 COMPONENTS MultimediaWidgets REQUIRED) # 
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# copy form auto generation
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# OPENGL LIBRARIES
# find_package(OpenGL REQUIRED) 

# set build mode directory options----------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/release)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
# find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# # setup include directory for this project
# include_directories(.)

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB forms ${PROJECT_SOURCE_DIR}/*.ui)
file(GLOB resources ${PROJECT_SOURCE_DIR}/images.qrc)
file(GLOB rc_icons ${PROJECT_SOURCE_DIR}/winapp.ico)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Qt libraries
# 
# add_executable(${PROJECT_NAME} ${sources} ${headers} ${forms} ${resources} ${rc_icons} appicon.rc)  #for windows
add_executable(${PROJECT_NAME} ${sources} ${headers} ${forms} ${resources} ${rc_icons})

target_link_libraries( ${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS ${PROJ_NAME} DESTINATION bin)
# install(FILES ${macs} DESTINATION bin)
