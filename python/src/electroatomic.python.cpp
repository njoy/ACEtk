// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace electroatomic {

  // declarations - ACE data components
  void wrapSubshellTransitionData( python::module&, python::module& );
  void wrapTabulatedAngularDistribution( python::module&, python::module& );
  void wrapTabulatedEnergyDistribution( python::module&, python::module& );

  // declarations - ACE table blocks
  void wrapElectronShellBlock( python::module&, python::module& );
  void wrapElectronSubshellBlock( python::module&, python::module& );
  void wrapPrincipalCrossSectionBlock( python::module&, python::module& );
  void wrapElasticCrossSectionBlock( python::module&, python::module& );
  void wrapExcitationBlock( python::module&, python::module& );
  void wrapBremsstrahlungBlock( python::module&, python::module& );
  void wrapSubshellTransitionDataBlock( python::module&, python::module& );
  void wrapElasticAngularDistributionBlock( python::module&, python::module& );
  void wrapEnergyDistributionBlock( python::module&, python::module& );
}

void wrapElectroatomic( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "electroatomic",
    "Electroatomic ACE blocks and components"
  );

  electroatomic::wrapSubshellTransitionData( submodule, viewmodule );
  electroatomic::wrapTabulatedAngularDistribution( submodule, viewmodule );
  electroatomic::wrapTabulatedEnergyDistribution( submodule, viewmodule );
  electroatomic::wrapElectronShellBlock( submodule, viewmodule );
  electroatomic::wrapElectronSubshellBlock( submodule, viewmodule );
  electroatomic::wrapPrincipalCrossSectionBlock( submodule, viewmodule );
  electroatomic::wrapElasticCrossSectionBlock( submodule, viewmodule );
  electroatomic::wrapExcitationBlock( submodule, viewmodule );
  electroatomic::wrapBremsstrahlungBlock( submodule, viewmodule );
  electroatomic::wrapSubshellTransitionDataBlock( submodule, viewmodule );
  electroatomic::wrapElasticAngularDistributionBlock( submodule, viewmodule );
  electroatomic::wrapEnergyDistributionBlock( submodule, viewmodule );
}
