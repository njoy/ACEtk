#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set( test_name "ACEtk.python.${name}.test" )
  add_test( NAME ${test_name}
            COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/${source}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
  set_tests_properties( ${test_name}
                        PROPERTIES ENVIRONMENT
                        PYTHONPATH=${ACEtk_PYTHONPATH}:$ENV{PYTHONPATH})

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding ACEtk Python unit testing" )

add_python_test( photoatomic.PrincipalCrossSectionBlock photoatomic/Test_ACEtk_photoatomic_PrincipalCrossSectionBlock.py )
add_python_test( photoatomic.IncoherentScatteringFunctionBlock photoatomic/Test_ACEtk_photoatomic_IncoherentScatteringFunctionBlock.py )
add_python_test( photoatomic.CoherentFormFactorBlock photoatomic/Test_ACEtk_photoatomic_CoherentFormFactorBlock.py )
add_python_test( photoatomic.FluorescenceDataBlock photoatomic/Test_ACEtk_photoatomic_FluorescenceDataBlock.py )
add_python_test( photoatomic.HeatingNumbersBlock photoatomic/Test_ACEtk_photoatomic_HeatingNumbersBlock.py )
add_python_test( photoatomic.ComptonProfile photoatomic/Test_ACEtk_photoatomic_ComptonProfile.py )
add_python_test( photoatomic.ComptonProfileBlock photoatomic/Test_ACEtk_photoatomic_ComptonProfileBlock.py )
add_python_test( photoatomic.PhotoelectricCrossSectionBlock photoatomic/Test_ACEtk_photoatomic_PhotoelectricCrossSectionBlock.py )
