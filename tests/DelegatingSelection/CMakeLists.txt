include(DelegatingSelection)

set(ds_foo "oog")

delegating_selection(ds_bar
  DEFAULT ds_foo
  DOCSTRING "delegation test case"
  OPTIONS oog boo zap)

set(ds_baz "fop" CACHE STRING "" FORCE)
set(ds_bax "0")
delegating_selection(ds_baz
  DEFAULT ds_bax
  DOCSTRING "non-delegation test case"
  OPTIONS fop mag buz)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/test.cpp
"
#include <cassert>
#include <string>

int main(){
  assert(std::string(\"${ds_bar}\") == \"oog\");
  assert(std::string(\"${ds_baz}\") == \"fop\");
}
")

add_executable(DelegatingSelection.test
  "${CMAKE_CURRENT_BINARY_DIR}/test.cpp")

add_test(
  NAME shacl.cmake.DelegatingSelection.test
  COMMAND DelegatingSelection.test)
