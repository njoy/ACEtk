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

add_python_test( photonuclear.PrincipalCrossSectionBlock    photonuclear/Test_ACEtk_photonuclear_PrincipalCrossSectionBlock.py )
add_python_test( photonuclear.SecondaryParticleLocatorBlock photonuclear/Test_ACEtk_photonuclear_SecondaryParticleLocatorBlock.py )

add_python_test( photoatomic.PrincipalCrossSectionBlock        photoatomic/Test_ACEtk_photoatomic_PrincipalCrossSectionBlock.py )
add_python_test( photoatomic.IncoherentScatteringFunctionBlock photoatomic/Test_ACEtk_photoatomic_IncoherentScatteringFunctionBlock.py )
add_python_test( photoatomic.CoherentFormFactorBlock           photoatomic/Test_ACEtk_photoatomic_CoherentFormFactorBlock.py )
add_python_test( photoatomic.FluorescenceDataBlock             photoatomic/Test_ACEtk_photoatomic_FluorescenceDataBlock.py )
add_python_test( photoatomic.HeatingNumbersBlock               photoatomic/Test_ACEtk_photoatomic_HeatingNumbersBlock.py )
add_python_test( photoatomic.ComptonProfile                    photoatomic/Test_ACEtk_photoatomic_ComptonProfile.py )
add_python_test( photoatomic.ComptonProfileBlock               photoatomic/Test_ACEtk_photoatomic_ComptonProfileBlock.py )
add_python_test( photoatomic.PhotoelectricCrossSectionBlock    photoatomic/Test_ACEtk_photoatomic_PhotoelectricCrossSectionBlock.py )

add_python_test( dosimetry.CrossSectionBlock dosimetry/Test_ACEtk_dosimetry_CrossSectionBlock.py )
add_python_test( dosimetry.CrossSectionData  dosimetry/Test_ACEtk_dosimetry_CrossSectionData.py )

add_python_test( electron.ElectronShellBlock              electron/Test_ACEtk_electron_ElectronShellBlock.py )
add_python_test( electron.ElectronSubshellBlock           electron/Test_ACEtk_electron_ElectronSubshellBlock.py )
add_python_test( electron.PrincipalCrossSectionBlock      electron/Test_ACEtk_electron_PrincipalCrossSectionBlock.py )
add_python_test( electron.ElasticCrossSectionBlock        electron/Test_ACEtk_electron_ElasticCrossSectionBlock.py )
add_python_test( electron.ExcitationBlock                 electron/Test_ACEtk_electron_ExcitationBlock.py )
add_python_test( electron.BremsstrahlungBlock             electron/Test_ACEtk_electron_BremsstrahlungBlock.py )
add_python_test( electron.SubshellTransitionData          electron/Test_ACEtk_electron_SubshellTransitionData.py )
add_python_test( electron.SubshellTransitionDataBlock     electron/Test_ACEtk_electron_SubshellTransitionDataBlock.py )
add_python_test( electron.TabulatedAngularDistribution    electron/Test_ACEtk_electron_TabulatedAngularDistribution.py )
add_python_test( electron.TabulatedEnergyDistribution     electron/Test_ACEtk_electron_TabulatedEnergyDistribution.py )
add_python_test( electron.ElasticAngularDistributionBlock electron/Test_ACEtk_electron_ElasticAngularDistributionBlock.py )
add_python_test( electron.EnergyDistributionBlock         electron/Test_ACEtk_electron_EnergyDistributionBlock.py )

add_python_test( thermal.CrossSectionBlock                 thermal/Test_ACEtk_thermal_CrossSectionBlock.py )
add_python_test( thermal.DiscreteCosines                   thermal/Test_ACEtk_thermal_DiscreteCosines.py )
add_python_test( thermal.DiscreteCosinesWithProbability    thermal/Test_ACEtk_thermal_DiscreteCosinesWithProbability.py )
add_python_test( thermal.ElasticAngularDistributionBlock   thermal/Test_ACEtk_thermal_ElasticAngularDistributionBlock.py )
add_python_test( thermal.InelasticAngularDistributionBlock thermal/Test_ACEtk_thermal_InelasticAngularDistributionBlock.py )
