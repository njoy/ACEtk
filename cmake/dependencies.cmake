cmake_minimum_required( VERSION 3.24 )
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( shacl_FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

shacl_FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         f843a47afbf868e1722cc741ba4d9b6d29d73f63  # tag: v0.4.0
    )

#######################################################################
# Load dependencies
#######################################################################

if(ACEtk.python)
  # Required to obtain version information
  find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
  shacl_FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         5b0a6fc2017fcc176545afe3e09c9f9885283242 # tag: v2.10.4
      )
  shacl_FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(ACEtk.tests)
  shacl_FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/Catch2
      GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
      )
  shacl_FetchContent_MakeAvailable(
      Catch2
    )
endif()

shacl_FetchContent_MakeAvailable(
    tools
    )
