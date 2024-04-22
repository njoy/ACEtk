// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace electron {

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

void wrapElectron( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "electron",
    "Electron ACE blocks and components"
  );

  electron::wrapSubshellTransitionData( submodule, viewmodule );
  electron::wrapTabulatedAngularDistribution( submodule, viewmodule );
  electron::wrapTabulatedEnergyDistribution( submodule, viewmodule );
  electron::wrapElectronShellBlock( submodule, viewmodule );
  electron::wrapElectronSubshellBlock( submodule, viewmodule );
  electron::wrapPrincipalCrossSectionBlock( submodule, viewmodule );
  electron::wrapElasticCrossSectionBlock( submodule, viewmodule );
  electron::wrapExcitationBlock( submodule, viewmodule );
  electron::wrapBremsstrahlungBlock( submodule, viewmodule );
  electron::wrapSubshellTransitionDataBlock( submodule, viewmodule );
  electron::wrapElasticAngularDistributionBlock( submodule, viewmodule );
  electron::wrapEnergyDistributionBlock( submodule, viewmodule );
}
