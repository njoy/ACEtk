
add_executable( ACEtk.block.ElectronTabulatedAngularDistribution.test ElectronTabulatedAngularDistribution.test.cpp )
target_compile_options( ACEtk.block.ElectronTabulatedAngularDistribution.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${ACEtk_appended_flags} )
target_link_libraries( ACEtk.block.ElectronTabulatedAngularDistribution.test PUBLIC ACEtk )
file( GLOB resources "resources/*" )
foreach( resource ${resources})
    file( COPY "${resource}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
endforeach()
add_test( NAME ACEtk.block.ElectronTabulatedAngularDistribution COMMAND ACEtk.block.ElectronTabulatedAngularDistribution.test )
