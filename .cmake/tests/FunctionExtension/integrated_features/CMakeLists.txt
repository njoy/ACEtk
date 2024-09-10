include(FunctionExtension)

backup(add_library)
function(add_library)
 previous_add_library("${ARGN}")
endfunction()

call(add_library integrated_features.test_library STATIC)
target_sources(integrated_features.test_library PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/test_source.cpp")
