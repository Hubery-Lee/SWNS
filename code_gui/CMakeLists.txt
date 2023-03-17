cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
# set(PROJ_NAME SWNS)
# project(${PROJ_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})  #设置程序安装目录
# set(CMAKE_INSTALL_PREFIX ../../) 

#============================================================================
if(UNIX)
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
 find_package(Geant4 REQUIRED ui_all vis_all)
else()
 find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/code_gui/include
		    ${Geant4_INCLUDE_DIR}
		    ${ROOT_INCLUDE_DIR}
)

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT REQUIRED)
#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/code_gui/src/*.cc  )
file(GLOB headers ${PROJECT_SOURCE_DIR}/code_gui/include/*.hh)
file(GLOB macs  ${PROJECT_SOURCE_DIR}/code_gui/macs/* )

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_subdirectory(gui)
# add_custom_target(SWNS-GUI DEPENDS gui)

add_executable(${PROJ_NAME} ${PROJECT_SOURCE_DIR}/code_gui/${PROJ_NAME}.cc ${sources})

# target_link_libraries(${PROJ_NAME} ${Geant4_LIBRARIES}          ${ROOT_LIBRARIES} 
		# -L${PROJECT_SOURCE_DIR}/lib SWNS-GUI)

target_link_libraries(${PROJ_NAME} ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS ${PROJ_NAME} DESTINATION bin)
install(FILES ${macs} DESTINATION bin)
#============================================================================
endif(UNIX)

#============================================================================
if(WIN32)

add_subdirectory(gui)
#============================================================================
endif(WIN32)


#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(_SCRIPTS)

foreach(_script ${_SCRIPTS})
configure_file(

${PROJECT_SOURCE_DIR}/${_script}
${PROJECT_BINARY_DIR}/../bin/${_script}

COPYONLY
)
endforeach()