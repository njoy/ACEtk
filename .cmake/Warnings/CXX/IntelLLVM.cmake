string(CONCAT shacl.cmake.Warnings.generator
  "$<$<BOOL:$<TARGET_PROPERTY:WARN_ERROR>>:"
    "$<IF:$<PLATFORM_ID:Windows>"
        ",/WX"
        ",-Werror>;>"
  "$<$<BOOL:$<TARGET_PROPERTY:WARN_ALL>>:"
    "$<IF:$<PLATFORM_ID:Windows>"
        ",/Wall"
        ",-Wall>;>"
  "$<$<BOOL:$<TARGET_PROPERTY:IntelLLVM_ENABLED_WARNINGS>>:"
    "$<IF:$<PLATFORM_ID:Windows>"
        ",/Qdiag-enable$<1::>"
        ",-diag-enable=>"
    "$<JOIN:$<TARGET_PROPERTY:IntelLLVM_ENABLED_WARNINGS>,$<COMMA>>;>"
  "$<$<BOOL:$<TARGET_PROPERTY:IntelLLVM_DISABLED_WARNINGS>>:"
    "$<IF:$<PLATFORM_ID:Windows>"
        ",/Qdiag-disable$<1::>"
        ",-diag-disable=>"
    "$<JOIN:$<TARGET_PROPERTY:IntelLLVM_DISABLED_WARNINGS>,$<COMMA>>;>")

target_compile_options(shacl::cmake::Warnings_CXX INTERFACE
  $<$<CXX_COMPILER_ID:IntelLLVM>:${shacl.cmake.Warnings.generator}>)

unset(shacl.cmake.Warnings.generator)
