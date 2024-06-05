include(CTest)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../..)

include(shacl_FetchContent)

include(dependencies.cmake)

# calls to find_package will use the libraries found in dependencies.cmake via FETCHCONTENT
find_package(Catch2 2.0 REQUIRED)
find_package(shacl-trait REQUIRED)

# Second inclusion does nothing and should not print anything extra
include(dependencies.cmake)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/bar.cpp
"#include <cassert>

// Test that find_package set the ${name}_FOUND variables to TRUE
 int main(){
   assert(\"${Catch2_FOUND}\" == \"1\" );
   assert(\"${shacl-trait_FOUND}\" == \"1\" );
 }
")

add_executable(Git.FetchContent.test ${CMAKE_CURRENT_BINARY_DIR}/bar.cpp)

add_test(
  NAME shacl.cmake.Git.FetchContent.test
  COMMAND Git.FetchContent.test)
