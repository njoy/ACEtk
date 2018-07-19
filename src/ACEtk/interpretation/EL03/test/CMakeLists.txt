
add_executable( ACEtk.interpretation.EL03.test
                el03.test.cpp
                RileyCrossSection.test.cpp
                MottScatteringCorrection.test.cpp
                AtomicLevels.test.cpp )
target_compile_options( ACEtk.interpretation.EL03.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${ACEtk_appended_flags} )
target_link_libraries( ACEtk.interpretation.EL03.test PUBLIC ACEtk ) 
file( GLOB resources "resources/*" )
foreach( resource ${resources})
    file( COPY "${resource}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
endforeach()
add_test( NAME ACEtk.interpretation.EL03 COMMAND ACEtk.interpretation.EL03.test )