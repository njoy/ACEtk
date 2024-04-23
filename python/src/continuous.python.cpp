// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace continuous {

  // declarations - ACE data components
  void wrapAngularDistributionData( python::module&, python::module& );
  void wrapCrossSectionData( python::module&, python::module& );
  void wrapDelayedNeutronPrecursorData( python::module&, python::module& );
  void wrapDiscretePhotonDistribution( python::module&, python::module& );
  void wrapDistributionGivenElsewhere( python::module&, python::module& );
  void wrapDistributionProbability( python::module&, python::module& );
  void wrapEnergyDependentWattSpectrum( python::module&, python::module& );
  void wrapEquiprobableAngularBins( python::module&, python::module& );
  void wrapEquiprobableOutgoingEnergyBinData( python::module&, python::module& );
  void wrapEquiprobableOutgoingEnergyBins( python::module&, python::module& );
  void wrapEvaporationSpectrum( python::module&, python::module& );
  void wrapFullyIsotropicDistribution( python::module&, python::module& );
  void wrapInterpolationData( python::module&, python::module& );
  void wrapIsotropicAngularDistribution( python::module&, python::module& );
  void wrapLevelScatteringDistribution( python::module&, python::module& );
  void wrapMultiDistributionData( python::module&, python::module& );
  void wrapNBodyPhaseSpaceDistribution( python::module&, python::module& );
  void wrapOutgoingEnergyDistributionData( python::module&, python::module& );
  void wrapParameterData( python::module&, python::module& );
  void wrapPolynomialFissionMultiplicity( python::module&, python::module& );
  void wrapProbabilityTable( python::module&, python::module& );
  void wrapSimpleMaxwellianFissionSpectrum( python::module&, python::module& );
  void wrapTabulatedAngleEnergyDistribution( python::module&, python::module& );
  void wrapTabulatedAngularDistribution( python::module&, python::module& );
  void wrapTabulatedAngularDistributionWithProbability( python::module&, python::module& );
  void wrapTabulatedEnergyAngleDistribution( python::module&, python::module& );
  void wrapTabulatedEnergyDistribution( python::module&, python::module& );
  void wrapTabulatedFissionMultiplicity( python::module&, python::module& );
  void wrapTabulatedKalbachMannDistribution( python::module&, python::module& );
  void wrapTabulatedMultiplicity( python::module&, python::module& );
  void wrapTabulatedSecondaryParticleMultiplicity( python::module&, python::module& );
  void wrapTwoBodyTransferDistribution( python::module&, python::module& );
  void wrapAngleEnergyDistributionData( python::module&, python::module& );
  void wrapEnergyAngleDistributionData( python::module&, python::module& );
  void wrapGeneralEvaporationSpectrum( python::module&, python::module& );
  void wrapKalbachMannDistributionData( python::module&, python::module& );
  void wrapPhotonProductionCrossSectionData( python::module&, python::module& );

  // declarations - ACE table blocks
  void wrapAngularDistributionBlock( python::module&, python::module& );
  void wrapCrossSectionBlock( python::module&, python::module& );
  void wrapDelayedNeutronPrecursorBlock( python::module&, python::module& );
  void wrapEnergyDistributionBlock( python::module&, python::module& );
  void wrapFissionMultiplicityBlock( python::module&, python::module& );
  void wrapFrameAndMultiplicityBlock( python::module&, python::module& );
  void wrapMultiplicityReactionNumberBlock( python::module&, python::module& );
  void wrapPhotonProductionBlock( python::module&, python::module& );
  void wrapPhotonProductionCrossSectionBlock( python::module&, python::module& );
  void wrapPrincipalCrossSectionBlock( python::module&, python::module& );
  void wrapProbabilityTableBlock( python::module&, python::module& );
  void wrapReactionNumberBlock( python::module&, python::module& );
  void wrapReactionQValueBlock( python::module&, python::module& );
  void wrapSecondaryParticleAngularDistributionBlock( python::module&, python::module& );
  void wrapSecondaryParticleEnergyDistributionBlock( python::module&, python::module& );
  void wrapSecondaryParticleInformationBlock( python::module&, python::module& );
  void wrapSecondaryParticleLocatorBlock( python::module&, python::module& );
  void wrapSecondaryParticleProductionBlock( python::module&, python::module& );
  void wrapSecondaryParticleProductionCrossSectionBlock( python::module&, python::module& );
  void wrapSecondaryParticleTypeBlock( python::module&, python::module& );
}

void wrapContinuous( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "continuous",
    "Continuous energy ACE blocks and components"
  );

  continuous::wrapAngularDistributionData( submodule, viewmodule );
  continuous::wrapCrossSectionData( submodule, viewmodule );
  continuous::wrapDelayedNeutronPrecursorData( submodule, viewmodule );
  continuous::wrapDiscretePhotonDistribution( submodule, viewmodule );
  continuous::wrapDistributionGivenElsewhere( submodule, viewmodule );
  continuous::wrapDistributionProbability( submodule, viewmodule );
  continuous::wrapEnergyDependentWattSpectrum( submodule, viewmodule );
  continuous::wrapEquiprobableAngularBins( submodule, viewmodule );
  continuous::wrapEquiprobableOutgoingEnergyBinData( submodule, viewmodule );
  continuous::wrapEquiprobableOutgoingEnergyBins( submodule, viewmodule );
  continuous::wrapEvaporationSpectrum( submodule, viewmodule );
  continuous::wrapFullyIsotropicDistribution( submodule, viewmodule );
  continuous::wrapInterpolationData( submodule, viewmodule );
  continuous::wrapIsotropicAngularDistribution( submodule, viewmodule );
  continuous::wrapLevelScatteringDistribution( submodule, viewmodule );
  continuous::wrapMultiDistributionData( submodule, viewmodule );
  continuous::wrapNBodyPhaseSpaceDistribution( submodule, viewmodule );
  continuous::wrapOutgoingEnergyDistributionData( submodule, viewmodule );
  continuous::wrapParameterData( submodule, viewmodule );
  continuous::wrapPolynomialFissionMultiplicity( submodule, viewmodule );
  continuous::wrapProbabilityTable( submodule, viewmodule );
  continuous::wrapSimpleMaxwellianFissionSpectrum( submodule, viewmodule );
  continuous::wrapTabulatedAngleEnergyDistribution( submodule, viewmodule );
  continuous::wrapTabulatedAngularDistribution( submodule, viewmodule );
  continuous::wrapTabulatedAngularDistributionWithProbability( submodule, viewmodule );
  continuous::wrapTabulatedEnergyAngleDistribution( submodule, viewmodule );
  continuous::wrapTabulatedEnergyDistribution( submodule, viewmodule );
  continuous::wrapTabulatedFissionMultiplicity( submodule, viewmodule );
  continuous::wrapTabulatedKalbachMannDistribution( submodule, viewmodule );
  continuous::wrapTabulatedMultiplicity( submodule, viewmodule );
  continuous::wrapTabulatedSecondaryParticleMultiplicity( submodule, viewmodule );
  continuous::wrapTwoBodyTransferDistribution( submodule, viewmodule );
  continuous::wrapAngleEnergyDistributionData( submodule, viewmodule );
  continuous::wrapEnergyAngleDistributionData( submodule, viewmodule );
  continuous::wrapGeneralEvaporationSpectrum( submodule, viewmodule );
  continuous::wrapKalbachMannDistributionData( submodule, viewmodule );
  continuous::wrapPhotonProductionCrossSectionData( submodule, viewmodule );
  continuous::wrapAngularDistributionBlock( submodule, viewmodule );
  continuous::wrapCrossSectionBlock( submodule, viewmodule );
  continuous::wrapDelayedNeutronPrecursorBlock( submodule, viewmodule );
  continuous::wrapEnergyDistributionBlock( submodule, viewmodule );
  continuous::wrapFissionMultiplicityBlock( submodule, viewmodule );
  continuous::wrapFrameAndMultiplicityBlock( submodule, viewmodule );
  continuous::wrapMultiplicityReactionNumberBlock( submodule, viewmodule );
  continuous::wrapPhotonProductionBlock( submodule, viewmodule );
  continuous::wrapPhotonProductionCrossSectionBlock( submodule, viewmodule );
  continuous::wrapPrincipalCrossSectionBlock( submodule, viewmodule );
  continuous::wrapProbabilityTableBlock( submodule, viewmodule );
  continuous::wrapReactionNumberBlock( submodule, viewmodule );
  continuous::wrapReactionQValueBlock( submodule, viewmodule );
  continuous::wrapSecondaryParticleAngularDistributionBlock( submodule, viewmodule );
  continuous::wrapSecondaryParticleEnergyDistributionBlock( submodule, viewmodule );
  continuous::wrapSecondaryParticleInformationBlock( submodule, viewmodule );
  continuous::wrapSecondaryParticleLocatorBlock( submodule, viewmodule );
  continuous::wrapSecondaryParticleProductionBlock( submodule, viewmodule );
  continuous::wrapSecondaryParticleProductionCrossSectionBlock( submodule, viewmodule );
  continuous::wrapSecondaryParticleTypeBlock( submodule, viewmodule );
}
