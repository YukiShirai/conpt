cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(pyconpt VERSION 0.0.1 LANGUAGES CXX)

####
# To enable testing, run cmake -DBUILD_TESTING=ON
####


#################################################

set(PROJECT pyconpt)

#################################################
# Colors
# Reference: https://stackoverflow.com/questions/18968979/how-to-make-colorized-message-with-cmake
string(ASCII 27 Esc)
set(ColourReset "${Esc}[m")
set(Red         "${Esc}[31m")
set(Yellow      "${Esc}[33m")

#################################################
# Out of Source Builds

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

#################################################
# Dependencies
# This must match the version you intend to use
find_package(Python 3.8 COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

# Two variables are created to hold the versions: Python_VERSION and PYTHON_VERSION_STRING
# - Python_VERSION: Holds specified version when find_package is called
# - PYTHON_VERSION_STRING: Holds the version of the found libraries
# If these do not match, the system is trying to build against python libaries that are not specified and should error
if ( NOT (${Python_VERSION} STREQUAL ${PYTHON_VERSION_STRING}) )
    message( FATAL_ERROR "${Red}Python versions do not match! The specified python version in the CMakeLists.txt file does not match the python libraries. Perhaps a virtual environment was not properly activated?${ColourReset}")
endif()

# Store the location of where the executable is
get_filename_component(PYTHON_LOCATION ${Python_EXECUTABLE} DIRECTORY)
# Check to make sure that the system libaries are not being used as preferred to use virtual environments. Users can proceed despite the warning.
if ( (PYTHON_LOCATION STREQUAL "/usr/bin") OR (PYTHON_LOCATION STREQUAL "/usr/local/bin") )
    message(WARNING "${Yellow}Using system python! If this is an accident, activate a virtual environment and restart cmake process! Otherwise proceed. ${ColourReset}")
endif()


#################################################
# Need this to keep runtime linking between cpp library and pybind library
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# message(CMAKE_INSTALL_PREFIX:)
# message(${CMAKE_INSTALL_PREFIX})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#################################################
# Build pybind shared module
pybind11_add_module(${PROJECT} SHARED src/bindings.cpp)

# Include all the directories of the previous projects. Maybe a better way to do this?
target_include_directories(${PROJECT}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

# Link with all the RomelaUtilities libraries 
target_link_libraries(${PROJECT}
	PRIVATE
		conpt
)

#################################################
### Installation

# Install into the found library
# WARNING: IF NO VIRTUALENV SELECTED, THIS WILL INSTALL INTO SYSTEM PYTHON LIBRARIES
install(TARGETS ${PROJECT} 
  LIBRARY DESTINATION "${Python_SITELIB}"
)
