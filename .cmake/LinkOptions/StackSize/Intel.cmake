string(CONCAT shacl.cmake.LinkOptions.StackSize.generator
  "$<$<OR:$<AND:$<STREQUAL:Fortran,$<TARGET_PROPERTY:LINKER_LANGUAGE>>,"
               "$<STREQUAL:Intel,${CMAKE_Fortran_COMPILER_ID}>>,"
         "$<AND:$<STREQUAL:C,$<TARGET_PROPERTY:LINKER_LANGUAGE>>,"
                "$<C_COMPILER_ID:Intel>>,"
         "$<AND:$<STREQUAL:CXX,$<TARGET_PROPERTY:LINKER_LANGUAGE>>,"
                "$<CXX_COMPILER_ID:Intel>>>:"
    "$<$<BOOL:$<TARGET_PROPERTY:LINK_STACK_SIZE>>:"
      "$<$<NOT:$<PLATFORM_ID:Windows>>:"
        "$<$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:CYGWIN>>:-Wl$<COMMA>"
          "$<$<PLATFORM_ID:Darwin>:-stack_size$<COMMA>>"
          "$<$<PLATFORM_ID:CYGWIN>:--stack$<COMMA>>"
          "$<TARGET_PROPERTY:LINK_STACK_SIZE>"
        ">"
      ">"
      "$<$<PLATFORM_ID:Windows>:-STACK:$<TARGET_PROPERTY:LINK_STACK_SIZE>>"
    ">"
  ">")

target_link_options(shacl::cmake::LinkOptions::StackSize INTERFACE
  ${shacl.cmake.LinkOptions.StackSize.generator})

unset(shacl.cmake.LinkOptions.StackSize.generator)
