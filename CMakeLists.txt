
cmake_minimum_required( VERSION 3.2 ) 
set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported configuration types" FORCE )
        
if( NOT ROOT_DIRECTORY )
    set( ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
    if ( NOT fetched_subprojects )
        if ( NOT PYTHON_EXECUTABLE )
            find_package( PythonInterp )
            if ( NOT PYTHONINTERP_FOUND )
                message( FATAL_ERROR "Python interpeter installation was not found." )
            endif()
        endif()
        execute_process( COMMAND ${PYTHON_EXECUTABLE} "./metaconfigure/fetch_subprojects.py"
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                         RESULT_VARIABLE fetch_failure )
        if ( NOT fetch_failure )
            set( fetched_subprojects TRUE CACHE BOOL "fetch script ran" )
        else()
            message( FATAL_ERROR "Failed to fetch dependencies" )
        endif()
    endif()
endif()

project( ACEtk LANGUAGES CXX )
get_directory_property( is_subproject PARENT_DIRECTORY )
include( CMakeDependentOption REQUIRED )

set( ACEtk_AppleClang_minimum_version 8.0 )
set( ACEtk_GNU_minimum_version 6.2 )
set( ACEtk_Clang_minimum_version 3.8 )

if( ACEtk_${CMAKE_CXX_COMPILER_ID}_minimum_version )
    if( CMAKE_CXX_COMPILER_VERSION AND
        CMAKE_CXX_COMPILER_VERSION VERSION_LESS
        ${ACEtk_${CMAKE_CXX_COMPILER_ID}_minimum_version} )
        message( FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} version must be greater than ${ACEtk_${CMAKE_CXX_COMPILER_ID}_minimum_version}" )
    endif()
endif()

# general properties
option( ACEtk_strict "Compile time warnings are converted to errors" ON )

# binary instrumentation
option( coverage "Enable binary instrumentation to collect test coverage information in the DEBUG configuration" )
option( profile_generate "Enable binary instrumentation to generation execution profiles in the RELEASE configuration which may be used to guide later optimization" )

# additional optimizations
option( link_time_optimization "Enable link time optimization in the RELEASE configuration" )
option( profile_use "In the RELEASE configuration, leverage previously generated exeution profile to inform optimization decisions" )
option( nonportable_optimization "Enable optimizations which compromise portability of resulting binary in the RELEASE configuration" )

# libraries and linking
option( static "Statically link component and environment libraries" OFF )
if ( static AND ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" ) )
    message( FATAL_ERROR "Static binaries not supported on OSX" )
endif()

CMAKE_DEPENDENT_OPTION( static_libraries "Statically link component libraries" OFF "NOT static" ON )

option( unit_tests "Compile the ACEtk unit tests and integrate with ctest" ON ) 

if ( profile_generate AND profile_use )
    message( FATAL_ERROR "Cannot both generate and use execution profile in the same configuration" )
endif()

if ( profile_generate )
    file( MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/profiling" )
endif()

set( ACEtk_AppleClang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( ACEtk_AppleClang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( ACEtk_AppleClang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_AppleClang_Darwin_strict_flags "-Werror" )
set( ACEtk_AppleClang_Darwin_coverage_flags "--coverage" )
set( ACEtk_AppleClang_Darwin_subproject_flags  )
set( ACEtk_AppleClang_Darwin_base_project_flags  )
set( ACEtk_AppleClang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_AppleClang_Darwin_link_time_optimization_flags "-flto" )
set( ACEtk_AppleClang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_AppleClang_Darwin_nonportable_optimization_flags "-march=native" )
set( ACEtk_AppleClang_Darwin_static_flags "-static" )
set( ACEtk_GNU_Linux_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( ACEtk_GNU_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ACEtk_GNU_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_GNU_Linux_strict_flags "-Werror" )
set( ACEtk_GNU_Linux_coverage_flags "--coverage" )
set( ACEtk_GNU_Linux_subproject_flags  )
set( ACEtk_GNU_Linux_base_project_flags  )
set( ACEtk_GNU_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_Linux_link_time_optimization_flags "-flto" )
set( ACEtk_GNU_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_Linux_nonportable_optimization_flags "-march=native" )
set( ACEtk_GNU_Linux_static_flags "-static" )
set( ACEtk_GNU_Darwin_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( ACEtk_GNU_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ACEtk_GNU_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_GNU_Darwin_strict_flags "-Werror" )
set( ACEtk_GNU_Darwin_coverage_flags "--coverage" )
set( ACEtk_GNU_Darwin_subproject_flags  )
set( ACEtk_GNU_Darwin_base_project_flags  )
set( ACEtk_GNU_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_Darwin_link_time_optimization_flags "-flto" )
set( ACEtk_GNU_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_Darwin_nonportable_optimization_flags "-march=native" )
set( ACEtk_GNU_Darwin_static_flags "-static" )
set( ACEtk_GNU_Windows_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( ACEtk_GNU_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ACEtk_GNU_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_GNU_Windows_strict_flags "-Werror" )
set( ACEtk_GNU_Windows_coverage_flags "--coverage" )
set( ACEtk_GNU_Windows_subproject_flags  )
set( ACEtk_GNU_Windows_base_project_flags  )
set( ACEtk_GNU_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_Windows_link_time_optimization_flags "-flto" )
set( ACEtk_GNU_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_Windows_nonportable_optimization_flags "-march=native" )
set( ACEtk_GNU_Windows_static_flags "-static" )
set( ACEtk_Clang_Linux_common_flags "-stdlib=libstdc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( ACEtk_Clang_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( ACEtk_Clang_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_Clang_Linux_strict_flags "-Werror" )
set( ACEtk_Clang_Linux_coverage_flags "--coverage" )
set( ACEtk_Clang_Linux_subproject_flags  )
set( ACEtk_Clang_Linux_base_project_flags  )
set( ACEtk_Clang_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_Linux_link_time_optimization_flags "-flto" )
set( ACEtk_Clang_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_Linux_nonportable_optimization_flags "-march=native" )
set( ACEtk_Clang_Linux_static_flags "-static" )
set( ACEtk_Clang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( ACEtk_Clang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( ACEtk_Clang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_Clang_Darwin_strict_flags "-Werror" )
set( ACEtk_Clang_Darwin_coverage_flags "--coverage" )
set( ACEtk_Clang_Darwin_subproject_flags  )
set( ACEtk_Clang_Darwin_base_project_flags  )
set( ACEtk_Clang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_Darwin_link_time_optimization_flags "-flto" )
set( ACEtk_Clang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_Darwin_nonportable_optimization_flags "-march=native" )
set( ACEtk_Clang_Darwin_static_flags "-static" )
set( ACEtk_Clang_Windows_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
set( ACEtk_Clang_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( ACEtk_Clang_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_Clang_Windows_strict_flags "-Werror" )
set( ACEtk_Clang_Windows_coverage_flags "--coverage" )
set( ACEtk_Clang_Windows_subproject_flags  )
set( ACEtk_Clang_Windows_base_project_flags  )
set( ACEtk_Clang_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_Windows_link_time_optimization_flags "-flto" )
set( ACEtk_Clang_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_Windows_nonportable_optimization_flags "-march=native" )
set( ACEtk_Clang_Windows_static_flags "-static" )
get_directory_property( is_subproject PARENT_DIRECTORY )

if( NOT TARGET hopscotch-map-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/hopscotch-map-adapter )
endif()

if( NOT TARGET range-v3-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/range-v3-adapter )
endif()

if( NOT TARGET catch-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/catch-adapter )
endif()

if( NOT TARGET disco )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/disco )
endif()

if( NOT TARGET fmt-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/fmt-adapter )
endif()

if( NOT TARGET spdlog-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/spdlog-adapter )
endif()

if( NOT TARGET Log )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/Log )
endif()

if( NOT TARGET header-utilities )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/header-utilities )
endif()

if( NOT TARGET date-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/date-adapter )
endif()

if( NOT TARGET variant-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/variant-adapter )
endif()

if( NOT TARGET hana-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/hana-adapter )
endif()

if( NOT TARGET dimwits )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/dimwits )
endif()

if( NOT TARGET interpolation )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/interpolation )
endif()


if ( NOT GIT_EXECUTABLE )
    find_package( Git )
    if ( NOT GIT_FOUND )
        message( FATAL_ERROR "git installation was not found." )
    endif()
endif()

execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
) 

message( STATUS "" )
message( STATUS "-----------------------------------------------------------" )
message( STATUS "" )
message( STATUS "ACEtk" )
message( STATUS "Git current branch: ${GIT_BRANCH}" )
message( STATUS "Git commit hash: ${GIT_HASH}" )
message( STATUS "" )
message( STATUS "-----------------------------------------------------------" )

add_library( ACEtk INTERFACE )
target_sources( ACEtk INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EPR.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/MP1.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EL03.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/MP1/DiscreteData.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/MP1/src/findStartOfBlock.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/MP1/src/totalCrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/MP1/src/cummulativeDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/MP1/src/scatteringAngles.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/MP1/src/fetch.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/MP1/src/energyGrid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EL03/AtomicLevels.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EL03/RileyCrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EL03/RadiativeStoppingPower.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EL03/MottScatteringCorrection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/NeutronYieldReferenceFrame.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Factors.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Yields.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/CrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/CrossSection/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/CrossSection/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution/Builder/src/energyGrid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution/Builder/src/cosineBins.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addYields.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/yields.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addCrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/crossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addAngularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addEnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Yields/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Yields/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/CrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/CrossSection/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Isotropic.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/interpolationFlag.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/cdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/cosineGrid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/equalSize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/pdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable/Builder/src/values.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder/src/addTabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder/src/addEquiprobable.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder/src/energyGrid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder/src/isotropic.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addCrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/crossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/neutronYield.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addAngularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addEnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/Q.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Law2Int.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LAW24.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Base.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/NBodyPhaseSpace.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/NBodyPhaseSpace/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/NBodyPhaseSpace/Builder/src/totalMassRatio.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/NBodyPhaseSpace/Builder/src/numberBodies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/Builder/src/energy.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/Builder/src/primaryFlag.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/cdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/interpolationParameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/pdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/energies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder/src/interpolationParameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder/src/cosines.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder/src/addEnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/Builder/src/addAngularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/Builder/src/cdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/Builder/src/interpolationParameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/Builder/src/cosineGrid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/Builder/src/pdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/addData.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/cdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/interpolationParameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/pdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/energies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Builder/src/addData.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Data.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Data/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Data/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Data/Builder/src/T.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Data/Builder/src/C.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Data/Builder/src/P.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Builder/src/addData.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Tabulated/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Tabulated/Builder/src/add.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Builder/src/restrictionEnergy.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Builder/src/energies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/cdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/interpolationParameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/angularDistributionSlope.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/precompoundFraction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/pdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/energies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Builder/src/addData.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins/Builder/src/outgoingEnergyTable.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LAW24/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LAW24/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LAW24/Builder/src/table.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering/Builder/src/QValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering/Builder/src/atomicWeightRatio.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder/src/equiprobableBins.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder/src/effectiveTemperature.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/Builder/src/restrictionEnergy.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/Builder/src/effectiveTemperature.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/cdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/interpolationParameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/pdf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/energies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Builder/src/addData.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/probabilities.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/addEnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum/Builder/src/restrictionEnergy.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum/Builder/src/effectiveTemperature.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Base/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/x.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/schemes.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/y.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/boundaries.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/energies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/src/ACEify_y.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder/src/values.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder/src/energyGrid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/Builder/src/decayConstant.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/Builder/src/probabilities.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/Builder/src/addEnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction/Builder/src/outgoingEnergies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction/Builder/src/crossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Tabulated/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Tabulated/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Tabulated/src/ACEify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Builder/src/polynomial.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Builder/src/precursors.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Builder/src/tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial/Builder/src/coefficients.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/captureCrossSections.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/heating.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/interpolationParameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/CDFs.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/equalSize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/inelasticCompetition.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/incidentEnergies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/otherAbsorption.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/fissionCrossSections.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/factors.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/totalCrossSections.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/elasticCrossSections.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addTotalGammaProduction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addReaction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/heating.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/totalDisappearanceCrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/ESZ.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addFissionMultiplicity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/totalGammaProduction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/totalCrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addProbabilityTable.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addPrecursor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addPhotonProductionReaction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addHeader.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/ACEifyEDs.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/energyGrid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/NU.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/precursors.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/SZA.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/photonProductionReaction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/fissionMultiplicity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EPR/Incoherent.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EPR/Coherent.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EPR/CRTP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EPR/CRTP/FormFactors.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/CDF.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/IsPositive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/IsCDF.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Sorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/StrictlyPositive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/IsSorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/IsStrictlyPositive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/IsCosineBins.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Positive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/CosineBins.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Positive/src/check.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Positive/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Positive/src/assignment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/CosineBins/src/check.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/CosineBins/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/CosineBins/src/assignment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/PDF/src/check.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/Unsorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/NotStrictlyPositive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/InvalidNeutronYield.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/NotPositive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/InvalidENDFInterpolationParameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/InvalidCDF.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/InvalidPDF.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/NotNormal.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/InvalidCosine.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/CDF/src/check.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/CDF/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/CDF/src/assignment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/StrictlyPositive/src/check.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/StrictlyPositive/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/StrictlyPositive/src/assignment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Sorted/src/check.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Sorted/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Sorted/src/assignment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/size.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/all.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/sorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/cosines.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/neutronYield.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/normal.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/strictlyPositive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/interpolationParameters.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/positive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/src/make_array.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/Parser.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/Parse.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/Parse/src/NXS.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/Parse/src/IZAW.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/Parse/src/JXS.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/Parse/src/XSS.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/NXS.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/JXS.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/AW.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/IZ.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/fetch.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/verifyIndex.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/XSS.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Data/src/name.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/Builder.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/String.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/Builder/src/szaid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/Builder/src/atomicWeightRatio.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/Builder/src/processDate.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/Builder/src/temperature.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/Builder/src/materialNumber.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/Builder/src/comment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/Builder/src/construct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/Builder/src/source.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/src/parse.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/src/print.hpp" )

target_include_directories( ACEtk INTERFACE src )

set( PREFIX ACEtk_${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME} )

target_link_libraries( ACEtk INTERFACE "$<$<AND:$<CONFIG:RELEASE>,$<BOOL:${link_time_optimization}>>:${${PREFIX}_RELEASE_flags};${${PREFIX}_link_time_optimization_flags}$<$<BOOL:${profile_generate}>:${${PREFIX}_profile_generate_flags};>$<$<BOOL:${profile_use}>:${${PREFIX}_profile_use_flags};>$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags};>>$<$<CONFIG:DEBUG>:$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags};>>$<$<BOOL:CXX_appended_flags>:${CXX_appended_flags};>$<$<BOOL:ACEtk_appended_flags>:${ACEtk_appended_flags};>" )

target_link_libraries( ACEtk INTERFACE hopscotch-map-adapter INTERFACE range-v3-adapter INTERFACE catch-adapter INTERFACE disco INTERFACE Log INTERFACE header-utilities INTERFACE date-adapter INTERFACE interpolation INTERFACE dimwits )

if( NOT is_subproject )
    enable_testing() 
    if ( unit_tests )
        add_subdirectory( src/ACEtk/Table/test )
        add_subdirectory( src/ACEtk/Table/Data/test )
        add_subdirectory( src/ACEtk/Table/Data/Parse/test )
        add_subdirectory( src/ACEtk/Table/Header/test )
        add_subdirectory( src/ACEtk/Table/Header/Builder/test )
        add_subdirectory( src/ACEtk/Table/Header/String/test )
        add_subdirectory( src/ACEtk/details/verify/test )
        add_subdirectory( src/ACEtk/details/verify/CDF/test )
        add_subdirectory( src/ACEtk/details/verify/CosineBins/test )
        add_subdirectory( src/ACEtk/details/verify/Positive/test )
        add_subdirectory( src/ACEtk/details/verify/Sorted/test )
        add_subdirectory( src/ACEtk/details/verify/StrictlyPositive/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LAW24/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/NBodyPhaseSpace/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Data/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Tabulated/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/CrossSection/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Yields/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/CrossSection/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction/Builder/test )
        add_subdirectory( src/ACEtk/interpretation/EL03/test )
        add_subdirectory( src/ACEtk/interpretation/EPR/test )
        add_subdirectory( src/ACEtk/interpretation/MP1/test )
    endif() 
endif()

install( DIRECTORY src/ DESTINATION include
         FILE_PERMISSIONS OWNER_READ OWNER_WRITE 
                          GROUP_READ 
                          WORLD_READ
         DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE 
                               GROUP_READ 
                               WORLD_READ
         FILES_MATCHING REGEX ".*\.h[+][+]$|.*\.hxx$|.*\.hpp$|.*\.hh$|.*\.h$"  )
