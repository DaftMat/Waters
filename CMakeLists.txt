cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0043 NEW)
cmake_policy(SET CMP0072 NEW)

#################################
#   Project variables
#################################
project(WaterProject)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No CMAKE_BUILD_TYPE, using default CMAKE_BUILD_TYPE=Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Win32 stuff
if (MSVC OR MSVC_IDE)
    # Use November CTP 2013 (constexpr and other non implemented stuff in the 2013 version)
#    if (MSVC_VERSION LESS 1800)
#        message(FATAL_ERROR
#                "This project requires C++11 stuff provided only with "
#                "Microsoft Visual C++ Compiler Nov 2013 CTP (v120_CTP_Nov2013).")
#    endif(MSVC_VERSION LESS 1800)
#
#    if (MSVC_VERSION EQUAL 1800)
#        #set(CMAKE_GENERATOR_TOOLSET "CTP_Nov2013" CACHE STRING "Platform Toolset" FORCE)
#    endif (MSVC_VERSION EQUAL 1800)
#
#    # Copy libs / targets in the correct directories
#    if ("${CMAKE_GENERATOR}" STREQUAL "NMake Makefiles")
#        set(PDB_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#    else()
#        foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
#            string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
#            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
#            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
#        endforeach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
#    endif()
    message(ERROR Unsupported Compiler.)
else(MSVC OR MSVC_IDE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic -Wextra -g -O3")
    if (NOT APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    endif()
endif(MSVC OR MSVC_IDE)

##################################
#   Build libraries and executables
##################################
set(ENGINE_LIBRARIES)
set(ENGINE_API)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/Applications)

include(CTest)
include(ConfigTests)
add_subdirectory(${TEST_DIR} EXCLUDE_FROM_ALL)