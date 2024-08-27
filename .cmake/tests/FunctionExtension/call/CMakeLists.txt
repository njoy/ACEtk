macro(foo arg)
  set(foo_output "${arg}")
endmacro()

macro(bar arg)
  set(bar_output "${arg}")
endmacro()

set(function_name foo)

# We can't do this ${function_name}(hello).
# call provides a workaround for the above limitation
call(${function_name} hello)
if(NOT foo_output STREQUAL "hello")
  message(FATAL_ERROR "foo_output should equal hello")
endif()

set(function_name bar)

call(${function_name} world)
if(NOT bar_output STREQUAL "world")
  message(FATAL_ERROR "bar_output should equal world")
endif()

function(variadic)
  set(testVar "${ARGN}" PARENT_SCOPE)
endfunction()

call(variadic a b c)
if( NOT testVar STREQUAL "a;b;c" )
  message(STATUS "testVar: ${testVar}" )
  message(FATAL_ERROR "testVar should equal a;b;c" )
endif()
