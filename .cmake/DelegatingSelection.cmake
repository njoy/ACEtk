cmake_minimum_required(VERSION 3.12.1)
include_guard(DIRECTORY)

include("${CMAKE_CURRENT_LIST_DIR}/config.cmake")
if(shacl.cmake.installation)
  get_property(
    shacl.cmake.installed_modules GLOBAL PROPERTY shacl.cmake.installed_modules)

  if(NOT "DelegatingSelection" IN_LIST shacl.cmake.installed_modules)
    set_property(GLOBAL APPEND PROPERTY
      shacl.cmake.installed_modules "DelegatingSelection")

    install(
      FILES "${CMAKE_CURRENT_LIST_FILE}"
      DESTINATION share/cmake/shacl/.cmake)
  endif()

  unset(shacl.cmake.installed_modules)
endif()

include_guard(GLOBAL)
function(delegating_selection variable)
  set(OPTIONS)
  set(UNARY_ARGUMENTS DEFAULT DOCSTRING)
  set(VARIADIC_ARGUMENTS OPTIONS)

  set(arguments)
  foreach(argument IN LISTS ARGN)
    if(argument MATCHES ".*[ ].*"
        OR argument MATCHES ".*[;].*"  # argument list
        OR argument MATCHES "\".*\"")  # quoted argument
      list(APPEND arguments "\"${argument}\"")
    elseif(argument STREQUAL "")
      list(APPEND arguments "\"\"")
    else()
      list(APPEND arguments "${argument}")
    endif()
  endforeach()

  cmake_parse_arguments(ds
    "${OPTIONS}"
    "${UNARY_ARGUMENTS}"
    "${VARIADIC_ARGUMENTS}" ${arguments})

  if(NOT DEFINED ds_DEFAULT)
    message(FATAL_ERROR
      "delegating_selection invoked without 'DEFAULT' argument")
  endif()

  if(NOT DEFINED ds_OPTIONS)
    message(FATAL_ERROR "selection invoked without 'OPTIONS' keyword")
  endif()

  set(options "default")
  foreach(option IN LISTS ds_OPTIONS)
    if(option MATCHES "\"(.*)\"")
      set(option "${CMAKE_MATCH_1}")
    endif()

    list(APPEND options "${option}")
  endforeach()

  if(ds_DOCSTRING)
    if(ds_DOCSTRING MATCHES "\"(.*)\"")
      set(ds_DOCSTRING "${CMAKE_MATCH_1}")
    endif()
    string(CONCAT docstring
      "${ds_DOCSTRING}\n"
      "When set to 'default', this variable assumes the value of ${ds_DEFAULT} ('${${ds_DEFAULT}}')")
  else()
    string(CONCAT docstring
      "When set to 'default', this variable assumes the value of ${ds_DEFAULT} ('${${ds_DEFAULT}}')")
  endif()

  if(NOT DEFINED ds_OPTIONS)
    message(FATAL_ERROR "selection invoked without 'OPTIONS' keyword")
  endif()

  set(${variable} "default" CACHE STRING "${docstring}")
  set_property(CACHE ${variable} PROPERTY STRINGS "${options}")
  set_property(CACHE ${variable} PROPERTY HELPSTRING "${docstring}")

  if(${variable} STREQUAL "default")
    set(${variable} "${${ds_DEFAULT}}")
  endif()

  if(NOT ${variable} IN_LIST options)
    message("${variable} set to ${${variable}}")
    set(error_message "${variable} must be one of:")
    foreach(option_string IN LISTS options)
      string(CONCAT error_message "${error_message}\n" "  ${option_string}")
    endforeach()
    message(FATAL_ERROR "${error_message}")
  endif()

  set(${variable} "${${variable}}" PARENT_SCOPE)
endfunction()
