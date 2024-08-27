cmake_minimum_required(VERSION 3.12.1)
include_guard(DIRECTORY)

include("${CMAKE_CURRENT_LIST_DIR}/config.cmake")
if(shacl.cmake.installation)
  get_property(
    shacl.cmake.installed_modules GLOBAL PROPERTY shacl.cmake.installed_modules)

  if(NOT "Selection" IN_LIST shacl.cmake.installed_modules)
    set_property(GLOBAL APPEND PROPERTY
      shacl.cmake.installed_modules "Selection")

    install(
      FILES "${CMAKE_CURRENT_LIST_FILE}"
      DESTINATION share/cmake/shacl/.cmake)
  endif()

  unset(shacl.cmake.installed_modules)
endif()

include_guard(GLOBAL)
function(selection variable)
  set(OPTIONS)
  set(UNARY_ARGUMENTS DEFAULT DOCSTRING)
  set(VARIADIC_ARGUMENTS OPTIONS)

  set(arguments)
  set(options)
  foreach(argument IN LISTS ARGN)
    if(argument STREQUAL ""            # argument empty string
        OR argument MATCHES ".*[ ].*"  # argument with embedded whitespace
        OR argument MATCHES ".*[;].*"  # argument list
        OR argument MATCHES ".*\".*")  # argument with embedded quotation
      list(APPEND arguments "\"${argument}\"")
    else()
      list(APPEND arguments "${argument}")
    endif()
  endforeach()

  cmake_parse_arguments(selection
    "${OPTIONS}"
    "${UNARY_ARGUMENTS}"
    "${VARIADIC_ARGUMENTS}" ${arguments})

  if(NOT DEFINED selection_OPTIONS)
    message(FATAL_ERROR "selection invoked without 'OPTIONS' keyword")
  endif()

  if(DEFINED selection_DEFAULT)
    if(NOT selection_DEFAULT IN_LIST selection_OPTIONS)
      string(CONCAT error_message
        "selection invoked with 'DEFAULT' argument not present in 'OPTIONS' list\n"
        "DEFAULT: ${selection_DEFAULT}\n\n"
        "${variable} must be one of:")
      foreach(option IN LISTS selection_OPTIONS)
        string(CONCAT error_message "${error_message}\n" "  ${option}")
      endforeach()
      message(FATAL_ERROR "${error_message}")
    endif()

    if(selection_DEFAULT MATCHES "\"(.*)\"")
      set(selection_DEFAULT "${CMAKE_MATCH_1}")
    endif()
  else()
    set(selection_DEFAULT "" )
    if(NOT "\"\"" IN_LIST selection_OPTIONS)
      list(APPEND selection_OPTIONS "\"\"")
    endif()
  endif()

  if(NOT DEFINED selection_DOCSTRING)
    message(FATAL_ERROR
      "selection invoked without 'DOCSTRING' argument")
  endif()
  if(selection_DOCSTRING MATCHES "\"(.*)\"")
    set(selection_DOCSTRING "${CMAKE_MATCH_1}")
  endif()

  if(DEFINED selection_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR
      "selection invoked with unrecognized arguments: ${selection_UNPARSED_ARGUMENTS}")
  endif()

  foreach(option IN LISTS selection_OPTIONS)
    if(option MATCHES "\"(.*)\"")
      set(option "${CMAKE_MATCH_1}")
    endif()

    set(options "${options};${option}")
  endforeach()

  set(${variable} "${selection_DEFAULT}" CACHE STRING ${selection_DOCSTRING})
  set_property(CACHE ${variable} PROPERTY STRINGS "${options}")

  if(NOT ${variable} IN_LIST options)
    message("${variable} set to '${${variable}}'")
    set(error_message "${variable} must be one of:")
    foreach(option IN LISTS options)
      string(CONCAT error_message "${error_message}\n" "  ${option}")
    endforeach()
    message(FATAL_ERROR "${error_message}")
  endif()
endfunction()
