// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace electron {

  // declarations - ACE table blocks
  void wrapBremsstrahlungAngularSpectrumBlock( python::module&, python::module& );
  void wrapBremsstrahlungCorrectionFactorBlock( python::module&, python::module& );
  void wrapBremsstrahlungEnergySpectrumBlock( python::module&, python::module& );
  void wrapBremsstrahlungHighFrequencyBlock( python::module&, python::module& );
  void wrapBremsstrahlungProductionBlock( python::module&, python::module& );
  void wrapMottScatteringCorrectionBlock( python::module&, python::module& );
  void wrapOscillatorBlock( python::module&, python::module& );
  void wrapRadiationStoppingPowerBlock( python::module&, python::module& );
  void wrapRileyCrossSectionBlock( python::module&, python::module& );
  void wrapTransitionEnergyBlock( python::module&, python::module& );
}

void wrapElectron( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "electron",
    "Electron ACE blocks and components"
  );

  electron::wrapBremsstrahlungAngularSpectrumBlock( submodule, viewmodule );
  electron::wrapBremsstrahlungCorrectionFactorBlock( submodule, viewmodule );
  electron::wrapBremsstrahlungEnergySpectrumBlock( submodule, viewmodule );
  electron::wrapBremsstrahlungHighFrequencyBlock( submodule, viewmodule );
  electron::wrapBremsstrahlungProductionBlock( submodule, viewmodule );
  electron::wrapMottScatteringCorrectionBlock( submodule, viewmodule );
  electron::wrapOscillatorBlock( submodule, viewmodule );
  electron::wrapRadiationStoppingPowerBlock( submodule, viewmodule );
  electron::wrapRileyCrossSectionBlock( submodule, viewmodule );
  electron::wrapTransitionEnergyBlock( submodule, viewmodule );
}
