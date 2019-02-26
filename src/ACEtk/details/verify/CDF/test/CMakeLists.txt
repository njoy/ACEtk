
add_executable( ACEtk.details.verify.CDF.test CDF.test.cpp )
target_compile_options( ACEtk.details.verify.CDF.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${ACEtk_appended_flags} )
target_link_libraries( ACEtk.details.verify.CDF.test PUBLIC ACEtk ) 
add_test( NAME ACEtk.details.verify.CDF COMMAND ACEtk.details.verify.CDF.test )