cmake_minimum_required(VERSION 3.13.0)

if(NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(shacl.cmake.is_subproject TRUE)
else()
  set(shacl.cmake.is_subproject FALSE)
endif()

if(shacl.cmake.is_subproject)
  if(NOT DEFINED INSTALL_SUBPROJECTS)
    option(INSTALL_SUBPROJECTS
      "Perform full installation of subproject dependencies" ON)
  endif()
endif()

include_guard(DIRECTORY)

if(NOT DEFINED shacl.cmake.installation)
  set(shacl.cmake.installation "default" CACHE STRING
  "Install to included shacl::cmake modules used by this project.
  When set to 'default', shacl::cmake projects will be installed for
  the highest level project and refer to the INSTALL_SUBPROJECTS cache
  variable in subprojects")

  set_property(CACHE shacl.cmake.installation PROPERTY STRINGS default ON OFF)
  mark_as_advanced(shacl.cmake.installation)
endif()

if(shacl.cmake.installation STREQUAL "default")
  if(shacl.cmake.is_subproject)
    set(shacl.cmake.install "${INSTALL_SUBPROJECTS}")
  else()
    set(shacl.cmake.install ON)
  endif()
endif()

include_guard(GLOBAL)
if(shacl.cmake.installation)
  install(FILES "${CMAKE_CURRENT_LIST_FILE}"
    DESTINATION share/cmake/shacl/.cmake)
endif()
