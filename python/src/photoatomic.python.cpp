// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace photoatomic {

  // declarations - ACE data components
  void wrapComptonProfile( python::module&, python::module& );

  // declarations - ACE table blocks
  void wrapComptonProfileBlock( python::module&, python::module& );
  void wrapPrincipalCrossSectionBlock( python::module&, python::module& );
  void wrapIncoherentScatteringFunctionBlock( python::module&, python::module& );
  void wrapCoherentFormFactorBlock( python::module&, python::module& );
  void wrapFluorescenceDataBlock( python::module&, python::module& );
  void wrapHeatingNumbersBlock( python::module&, python::module& );
  void wrapPhotoelectricCrossSectionBlock( python::module&, python::module& );
}

void wrapPhotoatomic( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "photoatomic",
    "Photoatomic ACE blocks and components"
  );

  photoatomic::wrapComptonProfile( submodule, viewmodule );
  photoatomic::wrapPrincipalCrossSectionBlock( submodule, viewmodule );
  photoatomic::wrapIncoherentScatteringFunctionBlock( submodule, viewmodule );
  photoatomic::wrapCoherentFormFactorBlock( submodule, viewmodule );
  photoatomic::wrapFluorescenceDataBlock( submodule, viewmodule );
  photoatomic::wrapHeatingNumbersBlock( submodule, viewmodule );
  photoatomic::wrapComptonProfileBlock( submodule, viewmodule );
  photoatomic::wrapPhotoelectricCrossSectionBlock( submodule, viewmodule );
}
