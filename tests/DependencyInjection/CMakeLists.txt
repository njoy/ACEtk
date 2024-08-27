include(DependencyInjection)

set(diexe.injections ${CMAKE_CURRENT_LIST_DIR}/exe_injected.cmake)
add_executable(diexe "")

set(dilib.injections ${CMAKE_CURRENT_LIST_DIR}/lib_injected.cmake)
add_library(dilib STATIC "")

target_link_libraries(diexe PRIVATE dilib)

add_test(
  NAME shacl.cmake.di_test
  COMMAND diexe
)
set_tests_properties(shacl.cmake.di_test PROPERTIES
  PASS_REGULAR_EXPRESSION "Hello World!"
)
