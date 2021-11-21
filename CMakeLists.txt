########################################################################
# Preamble
########################################################################
cmake_minimum_required( VERSION 3.14 )
project( ACEtk LANGUAGES CXX )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

option(ACEtk.tests "Build the ACEtk unit tests" OFF)
option( ACEtk.python "Build ACEtk python bindings" ON )
option( strict_compile
    "Treat all warnings as errors." ON
    )

# Compile flags
set( common_flags "-Wall" "-Wextra" "-Wpedantic" ) # i'm not sure why we manage flags this way...
set( strict_flags "-Werror" )                      # improving this will need to happen in the future for spack
set( release_flags "-O3" )
set( debug_flags "-O0" "-g" )


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

include_directories( src/ )

add_library( ACEtk INTERFACE )
target_include_directories( ACEtk INTERFACE src/ )
target_link_libraries( ACEtk
    INTERFACE Log
    INTERFACE catch-adapter
    INTERFACE dimwits
    INTERFACE disco
    INTERFACE interpolation
    INTERFACE hana-adapter
    INTERFACE header-utilities
    INTERFACE range-v3
    )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ACEtk : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if(ACEtk.python)
  pybind11_add_module( ACEtk.python
    python/src/ACEtk.python.cpp
    python/src/XsdirEntry.python.cpp
    python/src/Xsdir.python.cpp
    python/src/Header.python.cpp
    python/src/Data.python.cpp
    python/src/Table.python.cpp
    python/src/ReferenceFrame.python.cpp
    python/src/AngularDistributionType.python.cpp
    python/src/EnergyDistributionType.python.cpp
    python/src/block/InterpolationData.python.cpp
    python/src/block/CrossSectionData.python.cpp
    python/src/block/DosimetryCrossSectionData.python.cpp
    python/src/block/PrincipalCrossSectionBlock.python.cpp
    python/src/block/PolynomialFissionMultiplicity.python.cpp
    python/src/block/TabulatedFissionMultiplicity.python.cpp
    python/src/block/FissionMultiplicityBlock.python.cpp
    python/src/block/ReactionNumberBlock.python.cpp
    python/src/block/ReactionQValueBlock.python.cpp
    python/src/block/FrameAndMultiplicityBlock.python.cpp
    python/src/block/CrossSectionBlock.python.cpp
    python/src/block/DosimetryCrossSectionBlock.python.cpp
    python/src/block/SecondaryParticleTypeBlock.python.cpp
    python/src/block/EquiprobableAngularBins.python.cpp
    python/src/block/TabulatedAngularDistribution.python.cpp
    python/src/block/IsotropicAngularDistribution.python.cpp
    python/src/block/AngularDistributionData.python.cpp
    python/src/block/FullyIsotropicDistribution.python.cpp
    python/src/block/DistributionGivenElsewhere.python.cpp
    python/src/block/AngularDistributionBlock.python.cpp
    python/src/block/EquiprobableOutgoingEnergyBins.python.cpp
    python/src/block/EquiprobableOutgoingEnergyBinData.python.cpp
    python/src/block/LevelScatteringDistribution.python.cpp
    python/src/block/DiscretePhotonDistribution.python.cpp
    python/src/block/TabulatedOutgoingEnergyDistribution.python.cpp
    python/src/block/OutgoingEnergyDistributionData.python.cpp
    python/src/block/TabulatedKalbachMannDistribution.python.cpp
    python/src/block/KalbachMannDistributionData.python.cpp
    python/src/block/GeneralEvaporationSpectrum.python.cpp
    python/src/block/SimpleMaxwellianFissionSpectrum.python.cpp
    python/src/block/EvaporationSpectrum.python.cpp
    python/src/block/EnergyDistributionBlock.python.cpp
    python/src/ContinuousEnergyTable.python.cpp
    python/src/DosimetryTable.python.cpp
  )

  target_link_libraries( ACEtk.python PRIVATE ACEtk )
  target_include_directories( ACEtk.python PRIVATE python/src )
  target_compile_options( ACEtk.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( ACEtk.python PROPERTIES OUTPUT_NAME ACEtk )
  set_target_properties( ACEtk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( ACEtk.python PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  if( ACEtk.tests )
    include( cmake/unit_testing.cmake )
  endif()
endif()
