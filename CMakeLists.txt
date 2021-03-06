
cmake_minimum_required( VERSION 3.2 )
set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported configuration types" FORCE )
        
if ( NOT GIT_EXECUTABLE )
    find_package( Git 2.1 )
    if ( NOT GIT_FOUND )
        message( FATAL_ERROR "git installation was not found." )
    endif()
endif()

if( NOT ROOT_DIRECTORY )
    set( ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
    if ( NOT fetched_subprojects )
        if ( NOT PYTHON_EXECUTABLE )
            find_package( PythonInterp 3.4 )
            if ( NOT PYTHONINTERP_FOUND )
                message( FATAL_ERROR "Python interpreter installation was not found." )
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

if( NOT is_subproject )
    if( NOT ROOT_DIRECTORY )
        set( ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
    endif()
    if ( NOT PYTHON_EXECUTABLE )
        find_package( PythonInterp )
        if ( NOT PYTHONINTERP_FOUND )
            message( FATAL_ERROR "Python interpreter installation was not found." )
        endif()
    endif()
    execute_process( COMMAND ${PYTHON_EXECUTABLE} ./metaconfigure/signature.py ${CMAKE_BINARY_DIR}/signature
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE signature_failure )
    file( READ "${CMAKE_BINARY_DIR}/signature.json" SIGNATURE )
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
option( profile_use "In the RELEASE configuration, leverage previously generated execution profile to inform optimization decisions" )
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

set( ACEtk_AppleClang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
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
set( ACEtk_GNU_Darwin_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
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
set( ACEtk_GNU_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ACEtk_GNU_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ACEtk_GNU_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_GNU_MinGW_strict_flags "-Werror" )
set( ACEtk_GNU_MinGW_coverage_flags "--coverage" )
set( ACEtk_GNU_MinGW_subproject_flags  )
set( ACEtk_GNU_MinGW_base_project_flags  )
set( ACEtk_GNU_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_MinGW_link_time_optimization_flags "-flto" )
set( ACEtk_GNU_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_MinGW_nonportable_optimization_flags "-march=native" )
set( ACEtk_GNU_MinGW_static_flags "-static" )
set( ACEtk_GNU_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++17" )
set( ACEtk_GNU_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ACEtk_GNU_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_GNU_CYGWIN_strict_flags "-Werror" )
set( ACEtk_GNU_CYGWIN_coverage_flags "--coverage" )
set( ACEtk_GNU_CYGWIN_subproject_flags  )
set( ACEtk_GNU_CYGWIN_base_project_flags  )
set( ACEtk_GNU_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_CYGWIN_link_time_optimization_flags "-flto" )
set( ACEtk_GNU_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_GNU_CYGWIN_nonportable_optimization_flags "-march=native" )
set( ACEtk_GNU_CYGWIN_static_flags "-static" )
set( ACEtk_GNU_Windows_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
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
set( ACEtk_GNU_Linux_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
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
set( ACEtk_Clang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
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
set( ACEtk_Clang_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ACEtk_Clang_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ACEtk_Clang_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_Clang_MinGW_strict_flags "-Werror" )
set( ACEtk_Clang_MinGW_coverage_flags "--coverage" )
set( ACEtk_Clang_MinGW_subproject_flags  )
set( ACEtk_Clang_MinGW_base_project_flags  )
set( ACEtk_Clang_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_MinGW_link_time_optimization_flags "-flto" )
set( ACEtk_Clang_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_MinGW_nonportable_optimization_flags "-march=native" )
set( ACEtk_Clang_MinGW_static_flags "-static" )
set( ACEtk_Clang_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++17" )
set( ACEtk_Clang_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ACEtk_Clang_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( ACEtk_Clang_CYGWIN_strict_flags "-Werror" )
set( ACEtk_Clang_CYGWIN_coverage_flags "--coverage" )
set( ACEtk_Clang_CYGWIN_subproject_flags  )
set( ACEtk_Clang_CYGWIN_base_project_flags  )
set( ACEtk_Clang_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_CYGWIN_link_time_optimization_flags "-flto" )
set( ACEtk_Clang_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ACEtk_Clang_CYGWIN_nonportable_optimization_flags "-march=native" )
set( ACEtk_Clang_CYGWIN_static_flags "-static" )
set( ACEtk_Clang_Windows_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
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
set( ACEtk_Clang_Linux_common_flags "-stdlib=libstdc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
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
get_directory_property( is_subproject PARENT_DIRECTORY )

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

if( NOT TARGET range-v3-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/range-v3-adapter )
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
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/MP1.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/EL03.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/StandardWithCutoff.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/BPS.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/StandardWithoutCutoff.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP/S1.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP/S0.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP/S1/src/computeBounds.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP/S1/src/lowerBound.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP/S0/src/ceil.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP/S0/src/lowerBound.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP/S0/src/floor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP/src/stoppingPowers.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/interpretation/DEDX1/CRTP/src/outOfBounds.hpp"
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
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Positive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Positive/src/check.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Positive/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/Positive/src/assignment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/Unsorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/NotStrictlyPositive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/InvalidNeutronYield.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/NotPositive.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/InvalidENDFInterpolationParameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/InvalidCDF.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/InvalidPDF.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/exceptions/NotNormal.hpp"
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
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/details/verify/src/sorted.hpp"
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
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/String.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/Header/src/parse.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk/Table/src/print.hpp" )

target_include_directories( ACEtk INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/src src/ )

set( PREFIX ACEtk_${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME} )

target_link_libraries( ACEtk INTERFACE "$<$<AND:$<CONFIG:RELEASE>,$<BOOL:${link_time_optimization}>>:${${PREFIX}_RELEASE_flags};${${PREFIX}_link_time_optimization_flags}$<$<BOOL:${profile_generate}>:${${PREFIX}_profile_generate_flags};>$<$<BOOL:${profile_use}>:${${PREFIX}_profile_use_flags};>$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags};>>$<$<CONFIG:DEBUG>:$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags};>>$<$<BOOL:CXX_appended_flags>:${CXX_appended_flags};>$<$<BOOL:ACEtk_appended_flags>:${ACEtk_appended_flags};>" )

target_link_libraries( ACEtk INTERFACE catch-adapter INTERFACE disco INTERFACE Log INTERFACE header-utilities INTERFACE date-adapter INTERFACE interpolation INTERFACE dimwits )

if( NOT is_subproject )
    enable_testing() 
    if ( unit_tests )
        add_subdirectory( src/ACEtk/Table/test )
        add_subdirectory( src/ACEtk/Table/Data/test )
        add_subdirectory( src/ACEtk/Table/Data/Parse/test )
        add_subdirectory( src/ACEtk/Table/Header/test )
        add_subdirectory( src/ACEtk/Table/Header/String/test )
        add_subdirectory( src/ACEtk/details/verify/test )
        add_subdirectory( src/ACEtk/details/verify/CDF/test )
        add_subdirectory( src/ACEtk/details/verify/Positive/test )
        add_subdirectory( src/ACEtk/details/verify/Sorted/test )
        add_subdirectory( src/ACEtk/details/verify/StrictlyPositive/test )
        add_subdirectory( src/ACEtk/interpretation/ContinuousEnergyNeutron/test )
        add_subdirectory( src/ACEtk/interpretation/DEDX1/test )
        add_subdirectory( src/ACEtk/interpretation/EL03/test )
        add_subdirectory( src/ACEtk/interpretation/EPR/test )
        add_subdirectory( src/ACEtk/interpretation/MP1/test )
    endif() 
endif()

install( FILES "${CMAKE_BINARY_DIR}/signature.json"
         DESTINATION share/${CMAKE_PROJECT_NAME}
         PERMISSIONS OWNER_READ OWNER_WRITE
                     GROUP_READ
                     WORLD_READ
)
install( DIRECTORY src// DESTINATION include
         FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                          GROUP_READ
                          WORLD_READ
         DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE
                               GROUP_READ
                               WORLD_READ
         FILES_MATCHING REGEX ".*\.h[+][+]$|.*\.hxx$|.*\.hpp$|.*\.hh$|.*\.h$"  )

                    INCLUDE(CPack)
                    