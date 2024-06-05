backup(set_target_properties)

function(set_target_properties)
  previous_set_target_properties(${ARGN})
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/sink1" "${ARGN}")
endfunction()

backup(set_target_properties)

function(set_target_properties)
  previous_set_target_properties(${ARGN})
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/sink2" "${ARGN}")
endfunction()

add_library(FunctionExtension.set_target_properties INTERFACE)

set_target_properties(FunctionExtension.set_target_properties
  PROPERTIES INTERFACE_bar hello)

add_test(NAME shacl.cmake.set_target_properties_extension
  COMMAND "${CMAKE_COMMAND}" -E compare_files
  "${CMAKE_CURRENT_BINARY_DIR}/sink1"
  "${CMAKE_CURRENT_BINARY_DIR}/sink2")
