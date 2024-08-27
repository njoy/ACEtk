cmake_minimum_required(VERSION 3.12.1)

if(DEFINED CMAKE_C_COMPILER)
  if(NOT TARGET shacl::cmake::IntelLLVM::FloatingPoint::Speculation_C)
    add_library(shacl::cmake::IntelLLVM::FloatingPoint::Speculation_C
      INTERFACE IMPORTED GLOBAL)

    if(CMAKE_C_COMPILER_ID STREQUAL "IntelLLVM")
      set_property(TARGET shacl::cmake::IntelLLVM::FloatingPoint::Speculation_C
        APPEND PROPERTY COMPATIBLE_INTERFACE_STRING IntelLLVM_FLOATING_POINT_SPECULATION)
    endif()

    string(CONCAT shacl.cmake.IntelLLVM.FloatingPoint.Speculation.generator
      "$<$<BOOL:$<TARGET_PROPERTY:IntelLLVM_FLOATING_POINT_SPECULATION>>:"
        "$<$<C_COMPILER_ID:IntelLLVM>:"
          "$<IF:$<PLATFORM_ID:Windows>"
              ",/Qfp-speculation$<1::>"
              ",SHELL:-fp-speculation >"
          "$<TARGET_PROPERTY:IntelLLVM_FLOATING_POINT_SPECULATION>>>")

    target_compile_options(shacl::cmake::IntelLLVM::FloatingPoint::Speculation_C
      INTERFACE ${shacl.cmake.IntelLLVM.FloatingPoint.Speculation.generator})
  endif()
endif()

if(DEFINED CMAKE_CXX_COMPILER)
  if(NOT TARGET shacl::cmake::IntelLLVM::FloatingPoint::Speculation_CXX)
    add_library(shacl::cmake::IntelLLVM::FloatingPoint::Speculation_CXX
      INTERFACE IMPORTED GLOBAL)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
      set_property(TARGET shacl::cmake::IntelLLVM::FloatingPoint::Speculation_CXX
        APPEND PROPERTY COMPATIBLE_INTERFACE_STRING IntelLLVM_FLOATING_POINT_SPECULATION)
    endif()

    string(CONCAT shacl.cmake.IntelLLVM.FloatingPoint.Speculation.generator
      "$<$<BOOL:$<TARGET_PROPERTY:IntelLLVM_FLOATING_POINT_SPECULATION>>:"
        "$<$<CXX_COMPILER_ID:IntelLLVM>:"
          "$<IF:$<PLATFORM_ID:Windows>"
              ",/Qfp-speculation$<1::>"
              ",SHELL:-fp-speculation >"
          "$<TARGET_PROPERTY:IntelLLVM_FLOATING_POINT_SPECULATION>>>")

    target_compile_options(shacl::cmake::IntelLLVM::FloatingPoint::Speculation_CXX
      INTERFACE ${shacl.cmake.IntelLLVM.FloatingPoint.Speculation.generator})
  endif()
endif()

if(DEFINED CMAKE_Fortran_COMPILER)
  if(NOT TARGET shacl::cmake::IntelLLVM::FloatingPoint::Speculation_Fortran)
    add_library(shacl::cmake::IntelLLVM::FloatingPoint::Speculation_Fortran
      INTERFACE IMPORTED GLOBAL)

    if(CMAKE_Fortran_COMPILER_ID STREQUAL "IntelLLVM")
      set_property(TARGET shacl::cmake::IntelLLVM::FloatingPoint::Speculation_Fortran
        APPEND PROPERTY COMPATIBLE_INTERFACE_STRING IntelLLVM_FLOATING_POINT_SPECULATION)
    endif()

    string(CONCAT shacl.cmake.IntelLLVM.FloatingPoint.Speculation.generator
      "$<$<BOOL:$<TARGET_PROPERTY:IntelLLVM_FLOATING_POINT_SPECULATION>>:"
        "$<$<STREQUAL:IntelLLVM,${CMAKE_Fortran_COMPILER_ID}>:"
          "$<IF:$<PLATFORM_ID:Windows>"
              ",/Qfp-speculation$<1::>"
              ",SHELL:-fp-speculation >"
          "$<TARGET_PROPERTY:IntelLLVM_FLOATING_POINT_SPECULATION>>>")

    target_compile_options(shacl::cmake::IntelLLVM::FloatingPoint::Speculation_Fortran
      INTERFACE ${shacl.cmake.IntelLLVM.FloatingPoint.Speculation.generator})
  endif()
endif()

unset(shacl.cmake.IntelLLVM.FloatingPoint.Speculation.generator)

include_guard(DIRECTORY)

include("${CMAKE_CURRENT_LIST_DIR}/../../config.cmake")
if(shacl.cmake.installation)
  get_property(
    shacl.cmake.installed_modules GLOBAL PROPERTY shacl.cmake.installed_modules)

  if(NOT "IntelLLVM/FloatingPoint/Speculation" IN_LIST shacl.cmake.installed_modules)
    set_property(GLOBAL APPEND PROPERTY
      shacl.cmake.installed_modules "IntelLLVM/FloatingPoint/Speculation")

    install(
      FILES "${CMAKE_CURRENT_LIST_FILE}"
      DESTINATION share/cmake/shacl/.cmake/IntelLLVM/FloatingPoint)
  endif()

  unset(shacl.cmake.installed_modules)
endif()

include_guard(GLOBAL)
define_property(TARGET PROPERTY IntelLLVM_FLOATING_POINT_SPECULATION
BRIEF_DOCS
"IntelLLVM Fortran floating point speculation model"
FULL_DOCS
"This property specifies the IntelLLVM floating-point speculation approach.
Options are: fast, safe, strict, off")
