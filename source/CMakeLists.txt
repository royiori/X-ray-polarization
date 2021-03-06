#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Framework)

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
# CMake default setting:
#message("###> CMAKE_SKIP_RPATH: " ${CMAKE_SKIP_RPATH})
#message("###> CMAKE_SKIP_BUILD_RPATH: " ${CMAKE_SKIP_BUILD_RPATH})
#message("###> CMAKE_SKIP_INSTALL_RPATH: " ${CMAKE_SKIP_INSTALL_RPATH})
#set(CMAKE_SKIP_RPATH FALSE)           #add rpath to compiled executables (both in build/install)
#set(CMAKE_SKIP_BUILD_RPATH  FALSE)    #add rpath when building executables
#set(CMAKE_SKIP_INSTALL_RPATH FALSE)   #add rpath when installing executables

#message("###> CMAKE_BUILD_RPATH: " ${CMAKE_BUILD_RPATH})
#message("###> CMAKE_INSTALL_RPATH: " ${CMAKE_INSTALL_RPATH})
#set(CMAKE_BUILD_RPATH "./" "/usr/lib")   #set the rpath for building executables
#set(CMAKE_INSTALL_RPATH "./" "/usr/lib") #set the rpath for installing executables

#message("###> CMAKE_BUILD_WITH_INSTALL_RPATH: " ${CMAKE_BUILD_WITH_INSTALL_RPATH})
#set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) #build executables with ${CMAKE_INSTALL_RPATH}

#message("###> CMAKE_MACOSX_RPATH: " ${CMAKE_MACOSX_RPATH})
#set(CMAKE_MACOSX_RPATH 0)  #not use RPATH on MacOS 

##note that for MacOS, no RPATH is allowed for install
##a warning will be given when set INSTALL_RPATH

set(CMAKE_MACOSX_RPATH 1)

# the RPATH to be used when building  
set(CMAKE_BUILD_RPATH 
#   "/Users/liuqian/Work/work/geant4/examples-4.10.03.p03-build/extended/persistency/P01" 
   "/Users/tbn/Work/src/programs/geant/geant4.10.03.p03-install/lib" 
   "/Users/tbn/Qt5.6.0/5.6/clang_64/lib")

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT REQUIRED)

# ROOT version 6 required
if(ROOT_FOUND)
  STRING(REGEX MATCH "6.*" VERSION6MATCH ${ROOT_VERSION})
  if(NOT VERSION6MATCH)
    message(FATAL_ERROR "P01 requires ROOT 6")
  endif()
endif()

#----------------------------------------------------------------------------
# Find QT (required package)   
#
find_package(Qt COMPONENTS Widgets DBus REQUIRED)

#----------------------------------------------------------------------------
# executable requires shared libraries
#
if(NOT Geant4_shared_FOUND)
  message(FATAL_ERROR "Must use shared libraries")
endif()

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Generate dictionaries, add ROOT libraries properties
#
REFLEX_GENERATE_DICTIONARY(SimEvent include/SimEvent.hh SELECTION xml/selection.xml)
add_library(SimEventDict SHARED ${sources} Framework.cc SimEvent.cpp)
set(libsuffix .so)
set(ROOT_LIBRARY_PROPERTIES ${ROOT_LIBRARY_PROPERTIES} SUFFIX ${libsuffix})
set_target_properties(SimEventDict PROPERTIES ${ROOT_LIBRARY_PROPERTIES})
target_link_libraries(SimEventDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(Framework Framework.cc ${sources} ${headers})
target_link_libraries(Framework SimEventDict ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} Qt5::Widgets)
#Qt5::DBus)

# Not needed?
#add_executable(RootFileIO RootFileIO.cc ${sources} ${headers})
#target_link_libraries(RootFileIO SimEventDict ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} Qt5::Widgets Qt5::DBus)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build . This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(FRAMEWORK_SCRIPTS
  RootFileIO.C
  init_vis.mac
  vis.mac
  /mac/run.mac
  /mac/run_cxb.mac
  /mac/run_proton.mac
  /mac/run_e-.mac
  /mac/run_e+.mac
  )

foreach(_script ${FRAMEWORK_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(example DEPENDS Framework RootFileIO)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
#install(TARGETS Framework DESTINATION bin)


