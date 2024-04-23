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
                        PYTHONPATH=${tools_PYTHONPATH}:${ACEtk_PYTHONPATH}:$ENV{PYTHONPATH})

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding ACEtk Python unit testing" )

add_python_test( XsdirEntry Test_ACEtk_XsdirEntry.py )
add_python_test( Xsdir      Test_ACEtk_Xsdir.py )
add_python_test( Header     Test_ACEtk_Header.py )
add_python_test( Header201  Test_ACEtk_Header201.py )
add_python_test( Data       Test_ACEtk_Data.py )
add_python_test( Table      Test_ACEtk_Table.py )

add_python_test( continuous.EnergyDistributionBlock                      continuous/Test_ACEtk_continuous_EnergyDistributionBlock.py )
add_python_test( continuous.FissionMultiplicityBlock                     continuous/Test_ACEtk_continuous_FissionMultiplicityBlock.py )
add_python_test( continuous.PolynomialFissionMultiplicity                continuous/Test_ACEtk_continuous_PolynomialFissionMultiplicity.py )
add_python_test( continuous.TwoBodyTransferDistribution                  continuous/Test_ACEtk_continuous_TwoBodyTransferDistribution.py )
add_python_test( continuous.TabulatedSecondaryParticleMultiplicity       continuous/Test_ACEtk_continuous_TabulatedSecondaryParticleMultiplicity.py )
add_python_test( continuous.TabulatedMultiplicity                        continuous/Test_ACEtk_continuous_TabulatedMultiplicity.py )
add_python_test( continuous.TabulatedKalbachMannDistribution             continuous/Test_ACEtk_continuous_TabulatedKalbachMannDistribution.py )
add_python_test( continuous.TabulatedFissionMultiplicity                 continuous/Test_ACEtk_continuous_TabulatedFissionMultiplicity.py )
add_python_test( continuous.TabulatedEnergyDistribution                  continuous/Test_ACEtk_continuous_TabulatedEnergyDistribution.py )
add_python_test( continuous.TabulatedEnergyAngleDistribution             continuous/Test_ACEtk_continuous_TabulatedEnergyAngleDistribution.py )
add_python_test( continuous.TabulatedAngularDistributionWithProbability  continuous/Test_ACEtk_continuous_TabulatedAngularDistributionWithProbability.py )
add_python_test( continuous.TabulatedAngularDistribution                 continuous/Test_ACEtk_continuous_TabulatedAngularDistribution.py )
add_python_test( continuous.TabulatedAngleEnergyDistribution             continuous/Test_ACEtk_continuous_TabulatedAngleEnergyDistribution.py )
add_python_test( continuous.SimpleMaxwellianFissionSpectrum              continuous/Test_ACEtk_continuous_SimpleMaxwellianFissionSpectrum.py )
add_python_test( continuous.SecondaryParticleTypeBlock                   continuous/Test_ACEtk_continuous_SecondaryParticleTypeBlock.py )
add_python_test( continuous.SecondaryParticleProductionCrossSectionBlock continuous/Test_ACEtk_continuous_SecondaryParticleProductionCrossSectionBlock.py )
add_python_test( continuous.SecondaryParticleProductionBlock             continuous/Test_ACEtk_continuous_SecondaryParticleProductionBlock.py )
add_python_test( continuous.SecondaryParticleLocatorBlock                continuous/Test_ACEtk_continuous_SecondaryParticleLocatorBlock.py )
add_python_test( continuous.SecondaryParticleInformationBlock            continuous/Test_ACEtk_continuous_SecondaryParticleInformationBlock.py )
add_python_test( continuous.SecondaryParticleEnergyDistributionBlock     continuous/Test_ACEtk_continuous_SecondaryParticleEnergyDistributionBlock.py )
add_python_test( continuous.SecondaryParticleAngularDistributionBlock    continuous/Test_ACEtk_continuous_SecondaryParticleAngularDistributionBlock.py )
add_python_test( continuous.ReactionQValueBlock                          continuous/Test_ACEtk_continuous_ReactionQValueBlock.py )
add_python_test( continuous.ReactionNumberBlock                          continuous/Test_ACEtk_continuous_ReactionNumberBlock.py )
add_python_test( continuous.ProbabilityTableBlock                        continuous/Test_ACEtk_continuous_ProbabilityTableBlock.py )
add_python_test( continuous.ProbabilityTable                             continuous/Test_ACEtk_continuous_ProbabilityTable.py )
add_python_test( continuous.PrincipalCrossSectionBlock                   continuous/Test_ACEtk_continuous_PrincipalCrossSectionBlock.py )
add_python_test( continuous.PhotonProductionCrossSectionData             continuous/Test_ACEtk_continuous_PhotonProductionCrossSectionData.py )
add_python_test( continuous.PhotonProductionCrossSectionBlock            continuous/Test_ACEtk_continuous_PhotonProductionCrossSectionBlock.py )
add_python_test( continuous.PhotonProductionBlock                        continuous/Test_ACEtk_continuous_PhotonProductionBlock.py )
add_python_test( continuous.ParameterData                                continuous/Test_ACEtk_continuous_ParameterData.py )
add_python_test( continuous.OutgoingEnergyDistributionData               continuous/Test_ACEtk_continuous_OutgoingEnergyDistributionData.py )
add_python_test( continuous.NBodyPhaseSpaceDistribution                  continuous/Test_ACEtk_continuous_NBodyPhaseSpaceDistribution.py )
add_python_test( continuous.MultiplicityReactionNumberBlock              continuous/Test_ACEtk_continuous_MultiplicityReactionNumberBlock.py )
add_python_test( continuous.MultiDistributionData                        continuous/Test_ACEtk_continuous_MultiDistributionData.py )
add_python_test( continuous.LevelScatteringDistribution                  continuous/Test_ACEtk_continuous_LevelScatteringDistribution.py )
add_python_test( continuous.KalbachMannDistributionData                  continuous/Test_ACEtk_continuous_KalbachMannDistributionData.py )
add_python_test( continuous.IsotropicAngularDistribution                 continuous/Test_ACEtk_continuous_IsotropicAngularDistribution.py )
add_python_test( continuous.GeneralEvaporationSpectrum                   continuous/Test_ACEtk_continuous_GeneralEvaporationSpectrum.py )
add_python_test( continuous.FrameAndMultiplicityBlock                    continuous/Test_ACEtk_continuous_FrameAndMultiplicityBlock.py )
add_python_test( continuous.EvaporationSpectrum                          continuous/Test_ACEtk_continuous_EvaporationSpectrum.py )
add_python_test( continuous.EquiprobableOutgoingEnergyBins               continuous/Test_ACEtk_continuous_EquiprobableOutgoingEnergyBins.py )
add_python_test( continuous.EquiprobableOutgoingEnergyBinData            continuous/Test_ACEtk_continuous_EquiprobableOutgoingEnergyBinData.py )
add_python_test( continuous.EquiprobableAngularBins                      continuous/Test_ACEtk_continuous_EquiprobableAngularBins.py )
add_python_test( continuous.EnergyDependentWattSpectrum                  continuous/Test_ACEtk_continuous_EnergyDependentWattSpectrum.py )
add_python_test( continuous.EnergyAngleDistributionData                  continuous/Test_ACEtk_continuous_EnergyAngleDistributionData.py )
add_python_test( continuous.DistributionProbability                      continuous/Test_ACEtk_continuous_DistributionProbability.py )
add_python_test( continuous.DiscretePhotonDistribution                   continuous/Test_ACEtk_continuous_DiscretePhotonDistribution.py )
add_python_test( continuous.DelayedNeutronPrecursorData                  continuous/Test_ACEtk_continuous_DelayedNeutronPrecursorData.py )
add_python_test( continuous.DelayedNeutronPrecursorBlock                 continuous/Test_ACEtk_continuous_DelayedNeutronPrecursorBlock.py )
add_python_test( continuous.CrossSectionData                             continuous/Test_ACEtk_continuous_CrossSectionData.py )
add_python_test( continuous.CrossSectionBlock                            continuous/Test_ACEtk_continuous_CrossSectionBlock.py )
add_python_test( continuous.AngularDistributionData                      continuous/Test_ACEtk_continuous_AngularDistributionData.py )
add_python_test( continuous.AngularDistributionBlock                     continuous/Test_ACEtk_continuous_AngularDistributionBlock.py )
add_python_test( continuous.AngleEnergyDistributionData                  continuous/Test_ACEtk_continuous_AngleEnergyDistributionData.py )

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
