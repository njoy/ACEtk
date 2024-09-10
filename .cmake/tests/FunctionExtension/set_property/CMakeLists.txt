backup(set_property)

function(set_property)
  previous_set_property(${ARGN})
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/sink1" "${ARGN}")
endfunction()

backup(set_property)

function(set_property)
  previous_set_property(${ARGN})
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/sink2" "${ARGN}")
endfunction()

add_library(FunctionExtension.set_property INTERFACE)
set_property(TARGET FunctionExtension.set_property PROPERTY INTERFACE_bar hello)
add_test(NAME shacl.cmake.set_property_extension
  COMMAND "${CMAKE_COMMAND}" -E compare_files
  "${CMAKE_CURRENT_BINARY_DIR}/sink1"
  "${CMAKE_CURRENT_BINARY_DIR}/sink2")
