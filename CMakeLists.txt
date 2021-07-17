########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )
project( ACEtk LANGUAGES CXX )


########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

option( ACEtk_unit_tests
    "Compile the ACEtk unit tests and integrate with ctest" ON
    )
option( strict_compile
    "Treat all warnings as errors." ON
    )

# Compile flags
set( common_flags "-Wall" "-Wextra" "-Wpedantic" )
set( strict_flags "-Werror" )
set( release_flags "-O3" )
set( debug_flags "-O0" "-g" )


########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

message( STATUS "Using ${REPOSITORIES} repositories" )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()


########################################################################
# Project targets
########################################################################

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ACEtk : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

include_directories( src/ )

add_library( ACEtk INTERFACE
    )
target_include_directories( ACEtk INTERFACE src/ )
target_link_libraries( ACEtk
    INTERFACE Log
    INTERFACE catch-adapter
    INTERFACE date-adapter
    INTERFACE dimwits
    INTERFACE disco
    INTERFACE interpolation
    INTERFACE hana-adapter
    INTERFACE header-utilities
    INTERFACE range-v3-adapter
    )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ACEtk : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

include_directories( python/src/ )

pybind11_add_module( ACEtk.python
    EXCLUDE_FROM_ALL
    python/src/ACEtk.python.cpp
)
target_link_libraries( ACEtk.python PRIVATE ACEtk )
target_compile_options( ACEtk.python PRIVATE "-fvisibility=hidden" )
set_target_properties( ACEtk.python PROPERTIES OUTPUT_NAME ACEtk )
set_target_properties( ACEtk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
set_target_properties( ACEtk.python PROPERTIES POSITION_INDEPENDENT_CODE ON)

#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( ACEtk_unit_tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()
