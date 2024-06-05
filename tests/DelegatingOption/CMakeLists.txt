include(DelegatingOption)

set(do_foo "1")

delegating_option(do_bar
  DEFAULT do_foo
  DOCSTRING "delegation test case")

set(do_baz "ON" CACHE STRING "" FORCE)
set(do_bax "0")
delegating_option(do_baz
  DEFAULT do_bax
  DOCSTRING "non-delegation test case")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/test.cpp
"
#include <cassert>
#include <string>

int main(){
  assert(std::string(\"${do_bar}\") == \"ON\");
  assert(std::string(\"${do_baz}\") == \"ON\");
}
")

add_executable(DelegatingOption.test
  "${CMAKE_CURRENT_BINARY_DIR}/test.cpp")

add_test(
  NAME shacl.cmake.DelegatingOption.test
  COMMAND DelegatingOption.test)
