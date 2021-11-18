// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - generic ACE table
void wrapHeader( python::module&, python::module& );
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
  void wrapEquiprobableOutgoingEnergyBins( python::module&, python::module& );
  void wrapTabulatedAngularDistribution( python::module&, python::module& );
  void wrapIsotropicAngularDistribution( python::module&, python::module& );
  void wrapAngularDistributionData( python::module&, python::module& );
  void wrapFullyIsotropicDistribution( python::module&, python::module& );
  void wrapDistributionGivenElsewhere( python::module&, python::module& );
  void wrapLevelScatteringDistribution( python::module&, python::module& );
  void wrapDiscretePhotonDistribution( python::module&, python::module& );
  void wrapTabulatedOutgoingEnergyDistribution( python::module&, python::module& );
  void wrapOutgoingEnergyDistributionData( python::module&, python::module& );
  void wrapTabulatedKalbachMannDistribution( python::module&, python::module& );
  void wrapKalbachMannDistributionData( python::module&, python::module& );

  // declarations - ACE table blocks
  void wrapPrincipalCrossSectionBlock( python::module&, python::module& );
  void wrapFissionMultiplicityBlock( python::module&, python::module& );
  void wrapReactionNumberBlock( python::module&, python::module& );
  void wrapReactionQValueBlock( python::module&, python::module& );
  void wrapFrameAndMultiplicityBlock( python::module&, python::module& );
  void wrapCrossSectionBlock( python::module&, python::module& );
  void wrapDosimetryCrossSectionBlock( python::module&, python::module& );
  void wrapAngularDistributionBlock( python::module&, python::module& );
  void wrapEnergyDistributionBlock( python::module&, python::module& );
  void wrapSecondaryParticleTypeBlock( python::module&, python::module& );
}

// declarations - ACE table types
void wrapContinuousEnergyTable( python::module&, python::module& );
void wrapDosimetryTable( python::module&, python::module& );

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
  block::wrapEquiprobableOutgoingEnergyBins( module, viewmodule );
  block::wrapTabulatedAngularDistribution( module, viewmodule );
  block::wrapIsotropicAngularDistribution( module, viewmodule );
  block::wrapAngularDistributionData( module, viewmodule );
  block::wrapFullyIsotropicDistribution( module, viewmodule );
  block::wrapDistributionGivenElsewhere( module, viewmodule );
  block::wrapLevelScatteringDistribution( module, viewmodule );
  block::wrapDiscretePhotonDistribution( module, viewmodule );
  block::wrapTabulatedOutgoingEnergyDistribution( module, viewmodule );
  block::wrapOutgoingEnergyDistributionData( module, viewmodule );
  block::wrapTabulatedKalbachMannDistribution( module, viewmodule );
  block::wrapKalbachMannDistributionData( module, viewmodule );

  // wrap ACE table blocks
  block::wrapPrincipalCrossSectionBlock( module, viewmodule );
  block::wrapFissionMultiplicityBlock( module, viewmodule );
  block::wrapReactionNumberBlock( module, viewmodule );
  block::wrapReactionQValueBlock( module, viewmodule );
  block::wrapFrameAndMultiplicityBlock( module, viewmodule );
  block::wrapCrossSectionBlock( module, viewmodule );
  block::wrapDosimetryCrossSectionBlock( module, viewmodule );
  block::wrapAngularDistributionBlock( module, viewmodule );
  block::wrapEnergyDistributionBlock( module, viewmodule );
  block::wrapSecondaryParticleTypeBlock( module, viewmodule );

  // wrap ACE table types
  wrapContinuousEnergyTable( module, viewmodule );
  wrapDosimetryTable( module, viewmodule );
}
