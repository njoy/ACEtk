# Notes:
# fpscomp logicals does not work on ifx 2022.1.0 but the flag can be removed
# from here once it does.
# std_mod_proc_name breaks linking of almost all Fortran -> C bindings.

string(CONCAT shacl.cmake.Fortran.StandardCompliance.generator
  "$<$<STREQUAL:IntelLLVM,${CMAKE_Fortran_COMPILER_ID}>:"
    "$<IF:$<PLATFORM_ID:Windows>"
        ",/standard-semantics"
        ";/assume$<1::>nostd_mod_proc_name"
        ";/fpscomp$<1::>none"
        ",-standard-semantics"
        ";SHELL:-assume nostd_mod_proc_name"
        ";SHELL:-fpscomp none>>")

target_compile_options(shacl::cmake::Fortran::StandardCompliance
  INTERFACE ${shacl.cmake.Fortran.StandardCompliance.generator})

unset(shacl.cmake.Fortran.StandardCompliance.generator)
