cmake_minimum_required(VERSION 3.12.1)
include_guard(DIRECTORY)

include("${CMAKE_CURRENT_LIST_DIR}/../../config.cmake")
if(shacl.cmake.installation)
  get_property(
    shacl.cmake.installed_modules GLOBAL PROPERTY shacl.cmake.installed_modules)

  if(NOT "IntelLLVM/Fortran/Assumptions" IN_LIST shacl.cmake.installed_modules)
    set_property(GLOBAL APPEND PROPERTY
      shacl.cmake.installed_modules "IntelLLVM/Fortran/Assumptions")

    install(
      FILES "${CMAKE_CURRENT_LIST_FILE}"
      DESTINATION share/cmake/shacl/.cmake/IntelLLVM/Fortran)
  endif()

  unset(shacl.cmake.installed_modules)
endif()

if(NOT DEFINED CMAKE_Fortran_COMPILER)
  return()
endif()

include_guard(GLOBAL)
define_property(TARGET PROPERTY IntelLLVM_Fortran_ENABLED_ASSUMPTIONS
BRIEF_DOCS
"IntelLLVM assumption keywords (for Fortran) to ensable"
FULL_DOCS
"This property contains zero or more entries specifying assumption options
 used when compiling with the IntelLLVM Fortran compiler. Each entry corresponds
 to an assumption keyword, e.g., specifying `buffered_io` will add the
 `-assume buffered_io` or `/assume:buffered_io` flag as appropriate for
 the host platform.

 Multiple entries must be semicolon separated e.g. unused;unused")

define_property(TARGET PROPERTY IntelLLVM_Fortran_DISABLED_ASSUMPTIONS
BRIEF_DOCS
"IntelLLVM assumption keywords (for Fortran) to disable"
FULL_DOCS
"This property contains zero or more entries specifying assumption options
 used when compiling with the IntelLLVM Fortran compiler. Each entry corresponds
 to an assumption keyword, e.g., specifying `buffered_io` will add the
 `-assume nobuffered_io` or `/assume:nobuffered_io` flag as appropriate for
 the host platform.

 Multiple entries must be semicolon separated e.g. unused;unused")

add_library(shacl::cmake::IntelLLVM::Fortran::Assumptions INTERFACE IMPORTED GLOBAL)

string(CONCAT shacl.cmake.IntelLLVM.FortranAssumptions.generator
  "$<$<AND:$<STREQUAL:IntelLLVM,${CMAKE_Fortran_COMPILER_ID}>"
         ",$<BOOL:$<TARGET_PROPERTY:IntelLLVM_Fortran_ENABLED_ASSUMPTIONS>>>:"
    "$<IF:$<PLATFORM_ID:Windows>"
        ",/assume$<1::>"
        ",-assume;>"
    "$<JOIN:$<TARGET_PROPERTY:IntelLLVM_Fortran_ENABLED_ASSUMPTIONS>"
          ",$<COMMA>>>"
  "$<$<AND:$<STREQUAL:IntelLLVM,${CMAKE_Fortran_COMPILER_ID}>"
         ",$<BOOL:$<TARGET_PROPERTY:IntelLLVM_Fortran_DISABLED_ASSUMPTIONS>>>:"
    "$<IF:$<BOOL:$<TARGET_PROPERTY:IntelLLVM_Fortran_ENABLED_ASSUMPTIONS>>"
        ",$<COMMA>no"
        ",$<IF:$<PLATFORM_ID:Windows>"
             ",/assume$<1::>no"
             ",-assume;no>>"
    "$<JOIN:$<TARGET_PROPERTY:IntelLLVM_Fortran_DISABLED_ASSUMPTIONS>"
          ",$<COMMA>no>>")

target_compile_options(shacl::cmake::IntelLLVM::Fortran::Assumptions INTERFACE
  ${shacl.cmake.IntelLLVM.FortranAssumptions.generator})

unset(shacl.cmake.IntelLLVM.FortranAssumptions.generator)
