cmake_minimum_required( VERSION 3.27 )
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         v0.3.0
    GIT_SHALLOW     TRUE
    )

#######################################################################
# Load dependencies
#######################################################################

if(ACEtk.python)
  FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         v2.10.4
      GIT_SHALLOW     TRUE
      )
  FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(ACEtk.tests)
  FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/catch2
      GIT_TAG         v3.3.2
      GIT_SHALLOW     TRUE
      )
  FetchContent_MakeAvailable(
      Catch2 
    )
endif()

FetchContent_MakeAvailable(
    tools
)
