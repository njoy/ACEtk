########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.27 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( ACEtk
  VERSION 1.0.2
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
  "NOT ${subproject} OR DEFINED require.ACEtk.python " OFF
)

if ( ACEtk.python )
  set( require.tools.python CACHE BOOL ON )
endif()

option( ACEtk.installation "Install ACEtk" ON )

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

string( CONCAT prefix
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ACEtk : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( ACEtk INTERFACE )
add_library( njoy::ACEtk ALIAS ACEtk)

target_include_directories( ACEtk INTERFACE ${prefix} )

target_link_libraries( ACEtk
  INTERFACE
    njoy::tools
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ACEtk : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if (ACEtk.python AND NOT TARGET njoy::tools.python)
  message(WARNING "njoy::tools was not built with python enabled.  Disabling build of ACEtk's python API.")
  set(ACEtk.python OFF)
endif()

if(ACEtk.python)

  pybind11_add_module( ACEtk.python
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/ACEtk.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/XsdirEntry.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/Xsdir.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/Header.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/Header201.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/Data.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/Table.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/ReferenceFrame.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/AngularDistributionType.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/EnergyDistributionType.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/InterpolationData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/CrossSectionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/PrincipalCrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/PolynomialFissionMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TabulatedFissionMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/FissionMultiplicityBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/ReactionNumberBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/ReactionQValueBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/FrameAndMultiplicityBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/CrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/EquiprobableAngularBins.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TabulatedAngularDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TabulatedAngularDistributionWithProbability.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/IsotropicAngularDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/AngularDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/FullyIsotropicDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/DistributionGivenElsewhere.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/AngularDistributionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/SecondaryParticleAngularDistributionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/EquiprobableOutgoingEnergyBins.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/EquiprobableOutgoingEnergyBinData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/LevelScatteringDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/DiscretePhotonDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TabulatedEnergyDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/OutgoingEnergyDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/GeneralEvaporationSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/SimpleMaxwellianFissionSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/EvaporationSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/ParameterData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/EnergyDependentWattSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TabulatedKalbachMannDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/KalbachMannDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/NBodyPhaseSpaceDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TwoBodyTransferDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TabulatedEnergyAngleDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/EnergyAngleDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TabulatedAngleEnergyDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/AngleEnergyDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/DistributionProbability.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/MultiDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/EnergyDistributionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/SecondaryParticleEnergyDistributionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/DelayedNeutronPrecursorData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/PhotonProductionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/PhotonProductionCrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/MultiplicityReactionNumberBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TabulatedMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/TabulatedSecondaryParticleMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/PhotonProductionCrossSectionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/DelayedNeutronPrecursorBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/SecondaryParticleTypeBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/SecondaryParticleInformationBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/SecondaryParticleLocatorBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/SecondaryParticleProductionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/SecondaryParticleProductionCrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/ProbabilityTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/continuous/ProbabilityTableBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photonuclear.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photonuclear/PrincipalCrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photonuclear/SecondaryParticleLocatorBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photoatomic.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photoatomic/PrincipalCrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photoatomic/IncoherentScatteringFunctionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photoatomic/CoherentFormFactorBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photoatomic/FluorescenceDataBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photoatomic/HeatingNumbersBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photoatomic/ComptonProfile.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photoatomic/ComptonProfileBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/photoatomic/PhotoelectricCrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/dosimetry.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/dosimetry/CrossSectionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/dosimetry/CrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/ElectronShellBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/ElectronSubshellBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/PrincipalCrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/ElasticCrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/ExcitationBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/BremsstrahlungBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/SubshellTransitionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/SubshellTransitionDataBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/TabulatedAngularDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/ElasticAngularDistributionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/TabulatedEnergyDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/electron/EnergyDistributionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/thermal.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/thermal/CrossSectionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/thermal/DiscreteCosines.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/thermal/DiscreteCosinesWithProbability.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/thermal/ElasticAngularDistributionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/thermal/InelasticAngularDistributionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/ContinuousEnergyTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/DosimetryTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/ThermalScatteringTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/PhotoatomicTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/PhotonuclearTable.python.cpp
      )

  target_link_libraries(ACEtk.python PRIVATE njoy::ACEtk)
  add_dependencies( ACEtk.python njoy::tools.python)
  target_include_directories( ACEtk.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( ACEtk.python PRIVATE -fvisibility=hidden )
  set_target_properties( ACEtk.python PROPERTIES OUTPUT_NAME ACEtk )
  set_target_properties( ACEtk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( ACEtk.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building ACEtk's python API" )

  set( ACEtk_PYTHONPATH "${CMAKE_CURRENT_BINARY_DIR}" )
  # Append potential installation and build paths for tools python module
  set( tools_PYTHONPATH "${CMAKE_CURRENT_BINARY_DIR}/_deps/tools-build" )
  if (tools_DIR)
    set( tools_PYTHONPATH "${tools_PYTHONPATH}:${tools_DIR}/../../../lib64" )
  endif()

  if( ACEtk.tests )
    include( cmake/unit_testing_python.cmake )
  endif()

endif()

if( ${ACEtk.tests} )
  include( cmake/unit_testing.cmake )
endif()

#######################################################################
# Installation
#######################################################################

if(ACEtk.installation)
    include(CMakePackageConfigHelpers)

    install(TARGETS ACEtk EXPORT ACEtk-targets
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    install(EXPORT ACEtk-targets
      FILE "ACEtk-targets.cmake"
      NAMESPACE njoy::
      DESTINATION share/cmake/ACEtk
    )

    install(DIRECTORY src/
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp"
      PATTERN "*test*" EXCLUDE
    )

    string(TOLOWER ACEtk lowercasePackageName)

    write_basic_package_version_file("${lowercasePackageName}-config-version.cmake"
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion)

    configure_package_config_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${lowercasePackageName}-config.cmake.in
      ${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake
      INSTALL_DESTINATION share/cmake/ACEtk
    )

    install(FILES
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake"
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config-version.cmake"
      DESTINATION share/cmake/ACEtk
    )

    if(NOT subproject)
      set(CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory")
      set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
      include(CPack)
    endif()
endif()
