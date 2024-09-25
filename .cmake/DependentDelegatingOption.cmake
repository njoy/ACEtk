cmake_minimum_required(VERSION 3.12.1)
include_guard(DIRECTORY)

include("${CMAKE_CURRENT_LIST_DIR}/config.cmake")
if(shacl.cmake.installation)
  get_property(
    shacl.cmake.installed_modules GLOBAL PROPERTY shacl.cmake.installed_modules)

  if(NOT "DependentDelegatingOption" IN_LIST shacl.cmake.installed_modules)
    set_property(GLOBAL APPEND PROPERTY
      shacl.cmake.installed_modules "DependentDelegatingOption")

    install(
      FILES "${CMAKE_CURRENT_LIST_FILE}"
      DESTINATION share/cmake/shacl/.cmake)
  endif()

  unset(shacl.cmake.installed_modules)
endif()

include_guard(GLOBAL)
function(dependent_delegating_option variable)
  set(OPTIONS)
  set(UNARY_ARGUMENTS DEFAULT DOCSTRING FALLBACK)
  set(VARIADIC_ARGUMENTS CONDITION)

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

  cmake_parse_arguments(ddo
    "${OPTIONS}"
    "${UNARY_ARGUMENTS}"
    "${VARIADIC_ARGUMENTS}" ${arguments})

  if(NOT DEFINED ddo_DEFAULT)
    message(FATAL_ERROR
      "dependent_delegating_option invoked without 'DEFAULT' argument")
  endif()
  if(ddo_DEFAULT MATCHES "\"(.*)\"")
    set(ddo_DEFAULT "${CMAKE_MATCH_1}")
  endif()

  if(ddo_DOCSTRING)
    if(ddo_DOCSTRING MATCHES "\"(.*)\"")
      set(ddo_DOCSTRING "${CMAKE_MATCH_1}")
    endif()
    string(CONCAT docstring
      "${ddo_DOCSTRING}\n"
      "When set to 'default', ${variable} assumes the value of ${ddo_DEFAULT}")
  else()
    string(CONCAT docstring
      "When set to 'default', ${variable} assumes the value of ${ddo_DEFAULT}")
  endif()

  if(NOT DEFINED ddo_CONDITION)
    message(FATAL_ERROR
      "dependent_delegating_option invoked without 'CONDITION' argument")
  endif()

  if(NOT DEFINED ddo_FALLBACK)
    message(FATAL_ERROR
      "dependent_delegating_option invoked without 'FALLBACK' argument")
  endif()
  if(ddo_FALLBACK MATCHES "\"(.*)\"")
    set(ddo_FALLBACK "${CMAKE_MATCH_1}")
  endif()

  set(available TRUE)
  foreach(condition IN LISTS ddo_CONDITION)
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

  get_property(variable.set GLOBAL PROPERTY "${variable}.set" SET)

  if(available)
    if(NOT variable.set)
      set(${variable} "default" CACHE STRING "${docstring}")
      set(${variable} "${${variable}}" CACHE STRING "${docstring}" FORCE)
      set_property(CACHE ${variable} PROPERTY STRINGS default ON OFF)
    endif()
    if(${variable} STREQUAL "default")
      if(${ddo_DEFAULT})
        set(${variable} ON PARENT_SCOPE)
      else()
        set(${variable} OFF PARENT_SCOPE)
      endif()
    endif()
  else()
    if(DEFINED ${variable})
      set(${variable} "${${variable}}" CACHE INTERNAL "${docstring}")
    else(NOT variable.set)
      set(${variable} "default" CACHE INTERNAL "${docstring}")
    endif()
    set(${variable} "${ddo_FALLBACK}" PARENT_SCOPE)
  endif()

  set_property(GLOBAL PROPERTY "${variable}.set" "")
endfunction()
