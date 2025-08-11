// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace electron {

  // declarations - ACE table blocks
  void wrapTransitionEnergyBlock( python::module&, python::module& );
}

void wrapElectron( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "electron",
    "Electron ACE blocks and components"
  );

  electron::wrapTransitionEnergyBlock( submodule, viewmodule );
}
