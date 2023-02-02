cmake_minimum_required(VERSION 3.15)



# set(header_path "${PROJECT_SOURCE_DIR}"/include)

# setup header
set(header ${header_path}/CartPole.h
		   ${header_path}/TO_base.h
		   ${header_path}/test.h
		   )

# setup src files
set(src CartPole.cpp
        test.cpp)



add_library(conpt
            SHARED
            ${src})

add_library(conpt::conpt ALIAS conpt)
# Using the concept of namespace, this ALIAS command creates the variable with different name - to distinguish 

# option(BUILD_SHARED_LIBS "Build shared library" ON)

target_compile_features(conpt PUBLIC cxx_std_17)


target_include_directories(conpt INTERFACE 
                            # $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include> #/build/include 
                            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> #/conpt/include
                            $<INSTALL_INTERFACE:include> # for may case, INSTALL_INTERFACE is /usr/local
                            )

                            message(${CMAKE_BINARY_DIR}/)

set_target_properties(conpt PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib # static library (*.lib) is stored under /build/lib
LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib # dynamic library (*.so) is stored under /build/lib
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin # executable file (*.dll) is stored under /build/bin
)
                        

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(casadi REQUIRED)
find_package(param REQUIRED)
target_link_libraries(conpt
                        PUBLIC
                        Eigen3::Eigen
                        param
                        casadi) 


# install library files including .so
include(GNUInstallDirs)
install(TARGETS conpt # specify target to be installed
    EXPORT conpt-targets # export as conpt-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # static library for lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # library for lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # executable file for lib
    INCLUDES DESTINATION ${LIBLEGACY_INCLUDE_DIRS}
)


# sounds like this part is not necessary?
# not necessary but you want to use this one to see actual header files. 
# this install directory keeps saving all structure of build tree
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/conpt
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} #copy ${CMAKE_SOURCE_DIR}/include/conpt into ${CMAKE_INSTALL_INCLUDEDIR}, which is /usr/local/include
)


install(EXPORT conpt-targets
    FILE conpt-targets.cmake # actual one and this one is created from targe 
    # This one is used to simplify the process of linking to the library
    NAMESPACE conpt:: # even though it looks like conpt-targets, it uses conpt as name space
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/conpt # where to save
)

include(CMakePackageConfigHelpers)
# create config file
configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/conpt-config.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/conpt-config.cmake
    # used to provide information about how to use the library in other projects
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/conpt
)
# create version file
write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/conpt-config-version.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)
# install all configuration files (i.e., .cmake)
install(
    FILES
        ${CMAKE_BINARY_DIR}/cmake/conpt-config.cmake
        ${CMAKE_BINARY_DIR}/cmake/conpt-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/conpt
)

# export library
export(EXPORT conpt-targets
    FILE ${CMAKE_BINARY_DIR}/cmake/conpt-targets.cmake
    NAMESPACE conpt::
)
