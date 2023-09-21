// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - generic ACE table
void wrapHeader( python::module&, python::module& );
void wrapHeader201( python::module&, python::module& );
void wrapData( python::module&, python::module& );
void wrapTable( python::module&, python::module& );

// declarations - xsdir components
void wrapXsdirEntry( python::module&, python::module& );
void wrapXsdir( python::module&, python::module& );

// declarations - enumerators
void wrapReferenceFrame( python::module&, python::module& );
void wrapAngularDistributionType( python::module&, python::module& );
void wrapEnergyDistributionType( python::module&, python::module& );

namespace block {

  // declarations - ACE data components
  void wrapInterpolationData( python::module&, python::module& );
  void wrapTabulatedFissionMultiplicity( python::module&, python::module& );
  void wrapPolynomialFissionMultiplicity( python::module&, python::module& );
  void wrapCrossSectionData( python::module&, python::module& );
  void wrapDosimetryCrossSectionData( python::module&, python::module& );
  void wrapEquiprobableAngularBins( python::module&, python::module& );
  void wrapTabulatedAngularDistribution( python::module&, python::module& );
  void wrapTabulatedAngularDistributionWithProbability( python::module&, python::module& );
  void wrapIsotropicAngularDistribution( python::module&, python::module& );
  void wrapAngularDistributionData( python::module&, python::module& );
  void wrapFullyIsotropicDistribution( python::module&, python::module& );
  void wrapDistributionGivenElsewhere( python::module&, python::module& );
  void wrapEquiprobableOutgoingEnergyBins( python::module&, python::module& );
  void wrapEquiprobableOutgoingEnergyBinData( python::module&, python::module& );
  void wrapLevelScatteringDistribution( python::module&, python::module& );
  void wrapDiscretePhotonDistribution( python::module&, python::module& );
  void wrapTabulatedEnergyDistribution( python::module&, python::module& );
  void wrapOutgoingEnergyDistributionData( python::module&, python::module& );
  void wrapKalbachMannDistributionData( python::module&, python::module& );
  void wrapGeneralEvaporationSpectrum( python::module&, python::module& );
  void wrapSimpleMaxwellianFissionSpectrum( python::module&, python::module& );
  void wrapEvaporationSpectrum( python::module&, python::module& );
  void wrapParameterData( python::module&, python::module& );
  void wrapEnergyDependentWattSpectrum( python::module&, python::module& );
  void wrapTabulatedKalbachMannDistribution( python::module&, python::module& );
  void wrapNBodyPhaseSpaceDistribution( python::module&, python::module& );
  void wrapTwoBodyTransferDistribution( python::module&, python::module& );
  void wrapTabulatedEnergyAngleDistribution( python::module&, python::module& );
  void wrapEnergyAngleDistributionData( python::module&, python::module& );
  void wrapTabulatedAngleEnergyDistribution( python::module&, python::module& );
  void wrapAngleEnergyDistributionData( python::module&, python::module& );
  void wrapDistributionProbability( python::module&, python::module& );
  void wrapMultiDistributionData( python::module&, python::module& );
  void wrapTabulatedMultiplicity( python::module&, python::module& );
  void wrapTabulatedSecondaryParticleMultiplicity( python::module&, python::module& );
  void wrapPhotonProductionCrossSectionData( python::module&, python::module& );
  void wrapDelayedNeutronPrecursorData( python::module&, python::module& );
  void wrapProbabilityTable( python::module&, python::module& );
  void wrapThermalScatteringDiscreteCosines( python::module&, python::module& );
  void wrapThermalScatteringDiscreteCosinesWithProbability( python::module&, python::module& );
  void wrapPhotoatomicComptonProfile( python::module&, python::module& );
  void wrapPhotoatomicSubshellTransitionData( python::module&, python::module& );
  void wrapElectronTabulatedAngularDistribution( python::module&, python::module& );
  void wrapElectronTabulatedEnergyDistribution( python::module&, python::module& );

  // declarations - ACE table blocks
  void wrapPrincipalCrossSectionBlock( python::module&, python::module& );
  void wrapFissionMultiplicityBlock( python::module&, python::module& );
  void wrapReactionNumberBlock( python::module&, python::module& );
  void wrapReactionQValueBlock( python::module&, python::module& );
  void wrapFrameAndMultiplicityBlock( python::module&, python::module& );
  void wrapCrossSectionBlock( python::module&, python::module& );
  void wrapDosimetryCrossSectionBlock( python::module&, python::module& );
  void wrapPhotonProductionCrossSectionBlock( python::module&, python::module& );
  void wrapAngularDistributionBlock( python::module&, python::module& );
  void wrapSecondaryParticleAngularDistributionBlock( python::module&, python::module& );
  void wrapEnergyDistributionBlock( python::module&, python::module& );
  void wrapSecondaryParticleEnergyDistributionBlock( python::module&, python::module& );
  void wrapPhotonProductionBlock( python::module&, python::module& );
  void wrapMultiplicityReactionNumberBlock( python::module&, python::module& );
  void wrapDelayedNeutronPrecursorBlock( python::module&, python::module& );
  void wrapSecondaryParticleTypeBlock( python::module&, python::module& );
  void wrapSecondaryParticleInformationBlock( python::module&, python::module& );
  void wrapSecondaryParticleLocatorBlock( python::module&, python::module& );
  void wrapSecondaryParticleProductionBlock( python::module&, python::module& );
  void wrapSecondaryParticleProductionCrossSectionBlock( python::module&, python::module& );
  void wrapProbabilityTableBlock( python::module&, python::module& );
  void wrapThermalScatteringCrossSectionBlock( python::module&, python::module& );
  void wrapThermalScatteringElasticAngularDistributionBlock( python::module&, python::module& );
  void wrapThermalScatteringInelasticAngularDistributionBlock( python::module&, python::module& );
  void wrapPhotoatomicPrincipalCrossSectionBlock( python::module&, python::module& );
  void wrapIncoherentScatteringFunctionBlock( python::module&, python::module& );
  void wrapCoherentFormFactorBlock( python::module&, python::module& );
  void wrapPhotoatomicFluorescenceDataBlock( python::module&, python::module& );
  void wrapPhotoatomicHeatingNumbersBlock( python::module&, python::module& );
  void wrapPhotoatomicElectronShellBlock( python::module&, python::module& );
  void wrapPhotoatomicComptonProfileBlock( python::module&, python::module& );
  void wrapPhotonuclearPrincipalCrossSectionBlock( python::module&, python::module& );
  void wrapPhotonuclearSecondaryParticleLocatorBlock( python::module&, python::module& );
  void wrapPhotoatomicElectronSubshellBlock( python::module&, python::module& );
  void wrapPhotoatomicElectronCrossSectionBlock( python::module&, python::module& );
  void wrapPhotoatomicElectronExcitationBlock( python::module&, python::module& );
  void wrapPhotoatomicElectronBremsstrahlungBlock( python::module&, python::module& );
  void wrapPhotoelectricCrossSectionBlock( python::module&, python::module& );
  void wrapPhotoatomicSubshellTransitionDataBlock( python::module&, python::module& );
  void wrapElectronElasticAngularDistributionBlock( python::module&, python::module& );
  void wrapElectronEnergyDistributionBlock( python::module&, python::module& );
}

// declarations - ACE table types
void wrapContinuousEnergyTable( python::module&, python::module& );
void wrapDosimetryTable( python::module&, python::module& );
void wrapThermalScatteringTable( python::module&, python::module& );
void wrapPhotoatomicTable( python::module&, python::module& );
void wrapPhotonuclearTable( python::module&, python::module& );

/**
 *  @brief ACEtk python bindings
 *
 *  The name given here (ACEtk) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( ACEtk, module ) {

  // create the views submodule
  python::module viewmodule = module.def_submodule(

    "sequence",
    "sequence - ACE sequences (internal use only)"
  );

  // wrap some basic recurring views
  // none of these are supposed to be created directly by the user
  wrapBasicRandomAccessAnyViewOf< double >(
      viewmodule,
      "any_view< double, random_access >" );
  wrapBasicRandomAccessAnyViewOf< unsigned int >(
      viewmodule,
      "any_view< unsigned int, random_access >" );
  wrapBasicRandomAccessAnyViewOf< long >(
      viewmodule,
      "any_view< long, random_access >" );

  // wrap enumerators
  wrapReferenceFrame( module, viewmodule );
  wrapAngularDistributionType( module, viewmodule );
  wrapEnergyDistributionType( module, viewmodule );

  // wrap generic ACE table components
  wrapHeader( module, viewmodule );
  wrapHeader201( module, viewmodule );
  wrapData( module, viewmodule );
  wrapTable( module, viewmodule );

  // wrap xsdir components
  wrapXsdirEntry( module, viewmodule );
  wrapXsdir( module, viewmodule );

  // wrap data components
  block::wrapInterpolationData( module, viewmodule );
  block::wrapTabulatedFissionMultiplicity( module, viewmodule );
  block::wrapPolynomialFissionMultiplicity( module, viewmodule );
  block::wrapCrossSectionData( module, viewmodule );
  block::wrapDosimetryCrossSectionData( module, viewmodule );
  block::wrapEquiprobableAngularBins( module, viewmodule );
  block::wrapTabulatedAngularDistribution( module, viewmodule );
  block::wrapTabulatedAngularDistributionWithProbability( module, viewmodule );
  block::wrapIsotropicAngularDistribution( module, viewmodule );
  block::wrapAngularDistributionData( module, viewmodule );
  block::wrapFullyIsotropicDistribution( module, viewmodule );
  block::wrapDistributionGivenElsewhere( module, viewmodule );
  block::wrapLevelScatteringDistribution( module, viewmodule );
  block::wrapEquiprobableOutgoingEnergyBins( module, viewmodule );
  block::wrapEquiprobableOutgoingEnergyBinData( module, viewmodule );
  block::wrapDiscretePhotonDistribution( module, viewmodule );
  block::wrapTabulatedEnergyDistribution( module, viewmodule );
  block::wrapOutgoingEnergyDistributionData( module, viewmodule );
  block::wrapTabulatedKalbachMannDistribution( module, viewmodule );
  block::wrapGeneralEvaporationSpectrum( module, viewmodule );
  block::wrapSimpleMaxwellianFissionSpectrum( module, viewmodule );
  block::wrapEvaporationSpectrum( module, viewmodule );
  block::wrapParameterData( module, viewmodule );
  block::wrapEnergyDependentWattSpectrum( module, viewmodule );
  block::wrapKalbachMannDistributionData( module, viewmodule );
  block::wrapNBodyPhaseSpaceDistribution( module, viewmodule );
  block::wrapTwoBodyTransferDistribution( module, viewmodule );
  block::wrapTabulatedEnergyAngleDistribution( module, viewmodule );
  block::wrapEnergyAngleDistributionData( module, viewmodule );
  block::wrapTabulatedAngleEnergyDistribution( module, viewmodule );
  block::wrapAngleEnergyDistributionData( module, viewmodule );
  block::wrapDistributionProbability( module, viewmodule );
  block::wrapMultiDistributionData( module, viewmodule );
  block::wrapTabulatedSecondaryParticleMultiplicity( module, viewmodule );
  block::wrapTabulatedMultiplicity( module, viewmodule );
  block::wrapPhotonProductionCrossSectionData( module, viewmodule );
  block::wrapDelayedNeutronPrecursorData( module, viewmodule );
  block::wrapProbabilityTable( module, viewmodule );
  block::wrapThermalScatteringDiscreteCosines( module, viewmodule );
  block::wrapThermalScatteringDiscreteCosinesWithProbability( module, viewmodule );
  block::wrapPhotoatomicComptonProfile( module, viewmodule );
  block::wrapPhotoatomicSubshellTransitionData( module, viewmodule );
  block::wrapElectronTabulatedAngularDistribution( module, viewmodule );
  block::wrapElectronTabulatedEnergyDistribution( module, viewmodule );

  // wrap ACE table blocks
  block::wrapPrincipalCrossSectionBlock( module, viewmodule );
  block::wrapFissionMultiplicityBlock( module, viewmodule );
  block::wrapReactionNumberBlock( module, viewmodule );
  block::wrapReactionQValueBlock( module, viewmodule );
  block::wrapFrameAndMultiplicityBlock( module, viewmodule );
  block::wrapCrossSectionBlock( module, viewmodule );
  block::wrapDosimetryCrossSectionBlock( module, viewmodule );
  block::wrapPhotonProductionCrossSectionBlock( module, viewmodule );
  block::wrapAngularDistributionBlock( module, viewmodule );
  block::wrapSecondaryParticleAngularDistributionBlock( module, viewmodule );
  block::wrapEnergyDistributionBlock( module, viewmodule );
  block::wrapPhotonProductionBlock( module, viewmodule );
  block::wrapMultiplicityReactionNumberBlock( module, viewmodule );
  block::wrapDelayedNeutronPrecursorBlock( module, viewmodule );
  block::wrapSecondaryParticleEnergyDistributionBlock( module, viewmodule );
  block::wrapSecondaryParticleTypeBlock( module, viewmodule );
  block::wrapSecondaryParticleInformationBlock( module, viewmodule );
  block::wrapSecondaryParticleLocatorBlock( module, viewmodule );
  block::wrapSecondaryParticleProductionBlock( module, viewmodule );
  block::wrapSecondaryParticleProductionCrossSectionBlock( module, viewmodule );
  block::wrapProbabilityTableBlock( module, viewmodule );
  block::wrapThermalScatteringCrossSectionBlock( module, viewmodule );
  block::wrapThermalScatteringElasticAngularDistributionBlock( module, viewmodule );
  block::wrapThermalScatteringInelasticAngularDistributionBlock( module, viewmodule );
  block::wrapPhotoatomicPrincipalCrossSectionBlock( module, viewmodule );
  block::wrapIncoherentScatteringFunctionBlock( module, viewmodule );
  block::wrapCoherentFormFactorBlock( module, viewmodule );
  block::wrapPhotoatomicFluorescenceDataBlock( module, viewmodule );
  block::wrapPhotoatomicHeatingNumbersBlock( module, viewmodule );
  block::wrapPhotoatomicElectronShellBlock( module, viewmodule );
  block::wrapPhotoatomicComptonProfileBlock( module, viewmodule );
  block::wrapPhotonuclearPrincipalCrossSectionBlock( module, viewmodule );
  block::wrapPhotonuclearSecondaryParticleLocatorBlock( module, viewmodule );
  block::wrapPhotoatomicElectronSubshellBlock( module, viewmodule );
  block::wrapPhotoatomicElectronCrossSectionBlock( module, viewmodule );
  block::wrapPhotoatomicElectronExcitationBlock( module, viewmodule );
  block::wrapPhotoatomicElectronBremsstrahlungBlock( module, viewmodule );
  block::wrapPhotoelectricCrossSectionBlock( module, viewmodule );
  block::wrapPhotoatomicSubshellTransitionDataBlock( module, viewmodule );
  block::wrapElectronElasticAngularDistributionBlock( module, viewmodule );
  block::wrapElectronEnergyDistributionBlock( module, viewmodule );

  // wrap ACE table types
  wrapContinuousEnergyTable( module, viewmodule );
  wrapDosimetryTable( module, viewmodule );
  wrapThermalScatteringTable( module, viewmodule );
  wrapPhotoatomicTable( module, viewmodule );
  wrapPhotonuclearTable( module, viewmodule );
}
