include(Intel)

file(GENERATE
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/adherence.f90
  INPUT ${CMAKE_CURRENT_LIST_DIR}/adherence.f90.in)

add_executable(intel_standard_adherence
  ${CMAKE_CURRENT_BINARY_DIR}/adherence.f90)

target_link_libraries(intel_standard_adherence
  PRIVATE Intel::FortranStandardAdherence)

add_test(NAME shacl.cmake.Intel.FortranStandardAdherence
  COMMAND intel_standard_adherence)

if(CMAKE_Fortran_COMPILER_ID STREQUAL "Intel")
  if(WIN32)
    set(regex "/standard-semantics;/assume:")
  else()
    set(regex "-standard-semantics;-assume;")
  endif()
  set(regex "${regex}nostd_mod_proc_name")
endif()

set_tests_properties(shacl.cmake.Intel.FortranStandardAdherence
  PROPERTIES PASS_REGULAR_EXPRESSION "${regex}")
