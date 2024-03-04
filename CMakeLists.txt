########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( ACEtk
  VERSION 0.1.0
  LANGUAGES CXX
)

include( CTest )
include( CMakeDependentOption )
include( GNUInstallDirs )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

cmake_dependent_option(
  ACEtk.tests
  "Build the ACEtk unit tests and integrate with ctest" ON
  "BUILD_TESTING AND NOT ${subproject}" OFF
)
cmake_dependent_option(
  ACEtk.python
  "Build ACEtk python bindings" ON
  "NOT ${subproject}" OFF
)

########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

message( STATUS "Using ${REPOSITORIES} repositories" )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()


########################################################################
# Project targets
########################################################################

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ACEtk : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( ACEtk INTERFACE )
add_library( njoy::ACEtk ALIAS ACEtk )
target_include_directories( ACEtk
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries( ACEtk
  INTERFACE
    njoy::tools
    disco
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ACEtk : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( ACEtk.python )

  FetchContent_MakeAvailable( pybind11 )

  pybind11_add_module( ACEtk.python
      python/src/ACEtk.python.cpp
      python/src/XsdirEntry.python.cpp
      python/src/Xsdir.python.cpp
      python/src/Header.python.cpp
      python/src/Header201.python.cpp
      python/src/Data.python.cpp
      python/src/Table.python.cpp
      python/src/ReferenceFrame.python.cpp
      python/src/AngularDistributionType.python.cpp
      python/src/EnergyDistributionType.python.cpp
      python/src/continuous.python.cpp
      python/src/continuous/InterpolationData.python.cpp
      python/src/continuous/CrossSectionData.python.cpp
      python/src/continuous/PrincipalCrossSectionBlock.python.cpp
      python/src/continuous/PolynomialFissionMultiplicity.python.cpp
      python/src/continuous/TabulatedFissionMultiplicity.python.cpp
      python/src/continuous/FissionMultiplicityBlock.python.cpp
      python/src/continuous/ReactionNumberBlock.python.cpp
      python/src/continuous/ReactionQValueBlock.python.cpp
      python/src/continuous/FrameAndMultiplicityBlock.python.cpp
      python/src/continuous/CrossSectionBlock.python.cpp
      python/src/continuous/EquiprobableAngularBins.python.cpp
      python/src/continuous/TabulatedAngularDistribution.python.cpp
      python/src/continuous/TabulatedAngularDistributionWithProbability.python.cpp
      python/src/continuous/IsotropicAngularDistribution.python.cpp
      python/src/continuous/AngularDistributionData.python.cpp
      python/src/continuous/FullyIsotropicDistribution.python.cpp
      python/src/continuous/DistributionGivenElsewhere.python.cpp
      python/src/continuous/AngularDistributionBlock.python.cpp
      python/src/continuous/SecondaryParticleAngularDistributionBlock.python.cpp
      python/src/continuous/EquiprobableOutgoingEnergyBins.python.cpp
      python/src/continuous/EquiprobableOutgoingEnergyBinData.python.cpp
      python/src/continuous/LevelScatteringDistribution.python.cpp
      python/src/continuous/DiscretePhotonDistribution.python.cpp
      python/src/continuous/TabulatedEnergyDistribution.python.cpp
      python/src/continuous/OutgoingEnergyDistributionData.python.cpp
      python/src/continuous/GeneralEvaporationSpectrum.python.cpp
      python/src/continuous/SimpleMaxwellianFissionSpectrum.python.cpp
      python/src/continuous/EvaporationSpectrum.python.cpp
      python/src/continuous/ParameterData.python.cpp
      python/src/continuous/EnergyDependentWattSpectrum.python.cpp
      python/src/continuous/TabulatedKalbachMannDistribution.python.cpp
      python/src/continuous/KalbachMannDistributionData.python.cpp
      python/src/continuous/NBodyPhaseSpaceDistribution.python.cpp
      python/src/continuous/TwoBodyTransferDistribution.python.cpp
      python/src/continuous/TabulatedEnergyAngleDistribution.python.cpp
      python/src/continuous/EnergyAngleDistributionData.python.cpp
      python/src/continuous/TabulatedAngleEnergyDistribution.python.cpp
      python/src/continuous/AngleEnergyDistributionData.python.cpp
      python/src/continuous/DistributionProbability.python.cpp
      python/src/continuous/MultiDistributionData.python.cpp
      python/src/continuous/EnergyDistributionBlock.python.cpp
      python/src/continuous/SecondaryParticleEnergyDistributionBlock.python.cpp
      python/src/continuous/DelayedNeutronPrecursorData.python.cpp
      python/src/continuous/PhotonProductionBlock.python.cpp
      python/src/continuous/PhotonProductionCrossSectionBlock.python.cpp
      python/src/continuous/MultiplicityReactionNumberBlock.python.cpp
      python/src/continuous/TabulatedMultiplicity.python.cpp
      python/src/continuous/TabulatedSecondaryParticleMultiplicity.python.cpp
      python/src/continuous/PhotonProductionCrossSectionData.python.cpp
      python/src/continuous/DelayedNeutronPrecursorBlock.python.cpp
      python/src/continuous/SecondaryParticleTypeBlock.python.cpp
      python/src/continuous/SecondaryParticleInformationBlock.python.cpp
      python/src/continuous/SecondaryParticleLocatorBlock.python.cpp
      python/src/continuous/SecondaryParticleProductionBlock.python.cpp
      python/src/continuous/SecondaryParticleProductionCrossSectionBlock.python.cpp
      python/src/continuous/ProbabilityTable.python.cpp
      python/src/continuous/ProbabilityTableBlock.python.cpp
      python/src/photonuclear.python.cpp
      python/src/photonuclear/PrincipalCrossSectionBlock.python.cpp
      python/src/photonuclear/SecondaryParticleLocatorBlock.python.cpp
      python/src/photoatomic.python.cpp
      python/src/photoatomic/PrincipalCrossSectionBlock.python.cpp
      python/src/photoatomic/IncoherentScatteringFunctionBlock.python.cpp
      python/src/photoatomic/CoherentFormFactorBlock.python.cpp
      python/src/photoatomic/FluorescenceDataBlock.python.cpp
      python/src/photoatomic/HeatingNumbersBlock.python.cpp
      python/src/photoatomic/ComptonProfile.python.cpp
      python/src/photoatomic/ComptonProfileBlock.python.cpp
      python/src/photoatomic/PhotoelectricCrossSectionBlock.python.cpp
      python/src/dosimetry.python.cpp
      python/src/dosimetry/CrossSectionData.python.cpp
      python/src/dosimetry/CrossSectionBlock.python.cpp
      python/src/electron.python.cpp
      python/src/electron/ElectronShellBlock.python.cpp
      python/src/electron/ElectronSubshellBlock.python.cpp
      python/src/electron/PrincipalCrossSectionBlock.python.cpp
      python/src/electron/ElasticCrossSectionBlock.python.cpp
      python/src/electron/ExcitationBlock.python.cpp
      python/src/electron/BremsstrahlungBlock.python.cpp
      python/src/electron/SubshellTransitionData.python.cpp
      python/src/electron/SubshellTransitionDataBlock.python.cpp
      python/src/electron/TabulatedAngularDistribution.python.cpp
      python/src/electron/ElasticAngularDistributionBlock.python.cpp
      python/src/electron/TabulatedEnergyDistribution.python.cpp
      python/src/electron/EnergyDistributionBlock.python.cpp
      python/src/thermal.python.cpp
      python/src/thermal/CrossSectionBlock.python.cpp
      python/src/thermal/DiscreteCosines.python.cpp
      python/src/thermal/DiscreteCosinesWithProbability.python.cpp
      python/src/thermal/ElasticAngularDistributionBlock.python.cpp
      python/src/thermal/InelasticAngularDistributionBlock.python.cpp
      python/src/ContinuousEnergyTable.python.cpp
      python/src/DosimetryTable.python.cpp
      python/src/ThermalScatteringTable.python.cpp
      python/src/PhotoatomicTable.python.cpp
      python/src/PhotonuclearTable.python.cpp
      )

  target_link_libraries( ACEtk.python PRIVATE ACEtk )
  target_include_directories( ACEtk.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( ACEtk.python PRIVATE -fvisibility=hidden )
  set_target_properties( ACEtk.python PROPERTIES OUTPUT_NAME ACEtk )
  set_target_properties( ACEtk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( ACEtk.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building ACEtk's python API" )

  list( APPEND ACEtk_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR} )

  include( cmake/unit_testing_python.cmake )

endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  if( ACEtk.tests )
    include( cmake/unit_testing.cmake )
  endif()
endif()
