cmake_minimum_required(VERSION 3.12.1)
include_guard(DIRECTORY)

include("${CMAKE_CURRENT_LIST_DIR}/config.cmake")
if(shacl.cmake.installation)
  get_property(
    shacl.cmake.installed_modules GLOBAL PROPERTY shacl.cmake.installed_modules)

  if(NOT "DependentDelegatingSelection" IN_LIST shacl.cmake.installed_modules)
    set_property(GLOBAL APPEND PROPERTY
      shacl.cmake.installed_modules "DependentDelegatingSelection")

    install(
      FILES "${CMAKE_CURRENT_LIST_FILE}"
      DESTINATION share/cmake/shacl/.cmake)
  endif()

  unset(shacl.cmake.installed_modules)
endif()

include_guard(GLOBAL)
function(dependent_delegating_selection variable)
  set(OPTIONS)
  set(UNARY_ARGUMENTS DEFAULT DOCSTRING)
  set(VARIADIC_ARGUMENTS OPTIONS CONDITION FALLBACK)

  set(arguments)
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

  cmake_parse_arguments(dds
    "${OPTIONS}"
    "${UNARY_ARGUMENTS}"
    "${VARIADIC_ARGUMENTS}" ${arguments})

  if(NOT DEFINED dds_DEFAULT)
    message(FATAL_ERROR
      "dependent_delegating_selection invoked without 'DEFAULT' argument")
  endif()

  if(dds_DOCSTRING)
    string(CONCAT docstring
      "${dds_DOCSTRING}\n"
      "When set to 'default', ${variable} assumes the value of ${dds_DEFAULT}")
  else()
    string(CONCAT docstring
      "When set to 'default', ${variable} assumes the value of ${dds_DEFAULT}")
  endif()

  if(NOT DEFINED dds_CONDITION)
    message(FATAL_ERROR
      "dependent_delegating_selection invoked without 'CONDITION' argument")
  endif()

  if(NOT DEFINED dds_FALLBACK)
    message(FATAL_ERROR
      "dependent_delegating_selection invoked without 'FALLBACK' argument")
  endif()

  if(NOT DEFINED dds_OPTIONS)
    message(FATAL_ERROR "dependent_delegating_selection invoked without 'OPTIONS' keyword")
  endif()

  set(available TRUE)
  foreach(condition IN LISTS dds_CONDITION)
    if(condition MATCHES "\"(.*)\"")
      set(condition "${CMAKE_MATCH_1}")
    endif()
    string(REGEX REPLACE " +" ";" condition "${condition}")
    if(${condition})
    else()
      set(available FALSE)
      break()
    endif()
  endforeach()

  set(options "default;${dds_OPTIONS}")

  get_property(variable.set GLOBAL PROPERTY "${variable}.set" SET)

  if(${available})
    if(NOT variable.set)
      set(${variable} "default" CACHE STRING "${docstring}")
      set(${variable} "${${variable}}" CACHE STRING "${docstring}" FORCE)
      set_property(CACHE ${variable} PROPERTY STRINGS ${options})
    endif()
    if(${variable} STREQUAL "default")
      set(${variable} "${${dds_DEFAULT}}")
    endif()
  else()
    if(DEFINED ${variable})
      set(${variable} "${${variable}}" CACHE INTERNAL "${docstring}")
    else(NOT variable.set)
      set(${variable} "default" CACHE INTERNAL "${docstring}")
    endif()
    set(${variable} "${dds_FALLBACK}")
  endif()

  set_property(GLOBAL PROPERTY "${variable}.set" "")

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
