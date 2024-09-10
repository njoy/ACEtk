cmake_minimum_required(VERSION 3.12.1)
include_guard(DIRECTORY)

include("${CMAKE_CURRENT_LIST_DIR}/config.cmake")
if(shacl.cmake.installation)
  get_property(
    shacl.cmake.installed_modules GLOBAL PROPERTY shacl.cmake.installed_modules)

  if(NOT "IntelLLVM" IN_LIST shacl.cmake.installed_modules)
    set_property(GLOBAL APPEND PROPERTY shacl.cmake.installed_modules "IntelLLVM")

    install(
      FILES "${CMAKE_CURRENT_LIST_FILE}"
      DESTINATION share/cmake/shacl/.cmake)
  endif()

  unset(shacl.cmake.installed_modules)
endif()

include(IntelLLVM/Fortran/Assumptions)
include(IntelLLVM/FloatingPoint/Model)
include(IntelLLVM/FloatingPoint/Speculation)
