cmake_minimum_required( VERSION 3.27 )
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( shacl_FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

shacl_FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         v0.3.1
    GIT_SHALLOW     TRUE
    )

#######################################################################
# Load dependencies
#######################################################################

if(ACEtk.python)
  shacl_FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         v2.10.4
      GIT_SHALLOW     TRUE
      )
  shacl_FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(ACEtk.tests)
  shacl_FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/catch2
      GIT_TAG         v3.3.2
      GIT_SHALLOW     TRUE
      )
  shacl_FetchContent_MakeAvailable(
      Catch2 
    )
endif()

shacl_FetchContent_MakeAvailable(
    tools
)
