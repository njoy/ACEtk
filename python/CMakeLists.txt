if(ACEtk.python)

    pybind11_add_module( ACEtk.python
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ACEtk.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/XsdirEntry.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Xsdir.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Header.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Header201.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Data.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Table.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ReferenceFrame.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/AngularDistributionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/EnergyDistributionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/InterpolationData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/CrossSectionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/PrincipalCrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/PolynomialFissionMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TabulatedFissionMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/FissionMultiplicityBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/ReactionNumberBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/ReactionQValueBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/FrameAndMultiplicityBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/CrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/EquiprobableAngularBins.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TabulatedAngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TabulatedAngularDistributionWithProbability.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/IsotropicAngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/AngularDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/FullyIsotropicDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/DistributionGivenElsewhere.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/AngularDistributionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/SecondaryParticleAngularDistributionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/EquiprobableOutgoingEnergyBins.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/EquiprobableOutgoingEnergyBinData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/LevelScatteringDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/DiscretePhotonDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TabulatedEnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/OutgoingEnergyDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/GeneralEvaporationSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/SimpleMaxwellianFissionSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/EvaporationSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/ParameterData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/EnergyDependentWattSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TabulatedKalbachMannDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/KalbachMannDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/NBodyPhaseSpaceDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TwoBodyTransferDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TabulatedEnergyAngleDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/EnergyAngleDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TabulatedAngleEnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/AngleEnergyDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/DistributionProbability.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/MultiDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/EnergyDistributionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/SecondaryParticleEnergyDistributionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/DelayedNeutronPrecursorData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/PhotonProductionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/PhotonProductionCrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/MultiplicityReactionNumberBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TabulatedMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/TabulatedSecondaryParticleMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/PhotonProductionCrossSectionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/DelayedNeutronPrecursorBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/SecondaryParticleTypeBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/SecondaryParticleInformationBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/SecondaryParticleLocatorBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/SecondaryParticleProductionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/SecondaryParticleProductionCrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/ProbabilityTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/ProbabilityTableBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/continuous/UndefinedDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photonuclear.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photonuclear/PrincipalCrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photonuclear/SecondaryParticleLocatorBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photoatomic.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photoatomic/PrincipalCrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photoatomic/IncoherentScatteringFunctionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photoatomic/CoherentFormFactorBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photoatomic/FluorescenceDataBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photoatomic/HeatingNumbersBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photoatomic/ComptonProfile.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photoatomic/ComptonProfileBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/photoatomic/PhotoelectricCrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dosimetry.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dosimetry/CrossSectionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dosimetry/CrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/ElectronShellBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/ElectronSubshellBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/PrincipalCrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/ElasticCrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/ExcitationBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/BremsstrahlungBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/SubshellTransitionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/SubshellTransitionDataBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/TabulatedAngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/ElasticAngularDistributionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/TabulatedEnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/electron/EnergyDistributionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/thermal.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/thermal/CrossSectionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/thermal/DiscreteCosines.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/thermal/DiscreteCosinesWithProbability.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/thermal/ElasticAngularDistributionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/thermal/InelasticAngularDistributionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ContinuousEnergyTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DosimetryTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ThermalScatteringTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/PhotoatomicTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/PhotonuclearTable.python.cpp
        )

    target_link_libraries(ACEtk.python PRIVATE njoy::ACEtk)
    add_dependencies( ACEtk.python njoy::tools.python)
    target_include_directories( ACEtk.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )
    set_target_properties( ACEtk.python PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties( ACEtk.python PROPERTIES OUTPUT_NAME ACEtk )
    set_target_properties( ACEtk.python PROPERTIES LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR})
    set_target_properties( ACEtk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
    set_target_properties( ACEtk.python PROPERTIES POSITION_INDEPENDENT_CODE ON )
    # add all .so's that are installed with mcatk to the installed library rpath
    set_target_properties( ACEtk.python PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    # add all .so's that are linked to at build time to the installed library rpath
    set_target_properties( ACEtk.python PROPERTIES INSTALL_RPATH_USE_LINK_PATH ON)

    set(PyVersion "${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")
    set( py_library_install_prefix ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/python${PyVersion}/site-packages )

    if (ACEtk.installation)
        install( TARGETS ACEtk.python LIBRARY DESTINATION ${py_library_install_prefix} )
    endif()

    message( STATUS "Building ACEtk's python API" )

    # Append potential installation and build paths for tools python module
    set(ACEtk_PYTHONPATH "$<TARGET_FILE_DIR:ACEtk.python>")
    set(tools_PYTHONPATH "$<TARGET_FILE_DIR:njoy::tools.python>")

    # Windows and unix have different delimiter for paths
    if (WIN32)
	    set(PATH_DELIM "\;");
    else()
	    set(PATH_DELIM ":")
    endif()

    if (tools_DIR)
	    set(tools_PYTHONPATH_PARTS ${tools_PYTHONPATH} "${tools_DIR}/../../../${CMAKE_INSTALL_LIBDIR}" )
	    string( JOIN "${PATH_DELIM}" tools_PYTHONPATH ${tools_PYTHONPATH_PARTS})
    endif()

    if( ACEtk.tests )
        include( ${PROJECT_SOURCE_DIR}/cmake/unit_testing_python.cmake )
    endif()

    # generate python stubs if possible
    find_program(pybind11stubgen_exe pybind11-stubgen)

    set(PYTHONPATH_PARTS ${tools_PYTHONPATH} ${ACEtk_PYTHONPATH} $ENV{PYTHONPATH})
    string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

    set(stubdir "${CMAKE_CURRENT_SOURCE_DIR}/stubs/ACEtk")
    if (pybind11stubgen_exe)
        # the following command executes the pybind11-stubgen executable found via find_program
        # and puts its terminal output into pybind11-stubgen.log in the build tree.
        # The stubs get generated in the source tree so users can determine what changes if any were made to the stubs.
        # The stubs are then copied into the build tree so developers get the stubs when using the build tree's python bindings.
        # If the stubs fail to generate then this command exits gracefully and allows the build to continue.
        add_custom_command(
            TARGET ACEtk.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH_VALUE}" ${pybind11stubgen_exe} ACEtk -o ${CMAKE_CURRENT_SOURCE_DIR}/stubs &> ${CMAKE_CURRENT_BINARY_DIR}/pybind11-stubgen.log || true
            COMMAND ${CMAKE_COMMAND} -E rename ${stubdir}/__init__.pyi ${stubdir}/ACEtk.pyi &> /dev/null || true
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Building ACEtk's python stub files via pybind11-stubgen. See pybind11-stubgen.log for details."
            VERBATIM
        )

    else()
        # copy stub files to build tree even if pybind11stubgen isn't available.
        add_custom_command(
            TARGET ACEtk.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()

    # install stubs so the installed binaries play nice with IDEs
    if (ACEtk.installation)
        install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stubs/ACEtk/ DESTINATION ${py_library_install_prefix} )
    endif()

endif() # end ACEtk.python check
