// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace photonuclear {

  // declarations - ACE data components

  // declarations - ACE table blocks
  void wrapPrincipalCrossSectionBlock( python::module&, python::module& );
  void wrapSecondaryParticleLocatorBlock( python::module&, python::module& );
}

void wrapPhotonuclear( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "photonuclear",
    "Photonuclear ACE blocks and components"
  );

  photonuclear::wrapPrincipalCrossSectionBlock( submodule, viewmodule );
  photonuclear::wrapSecondaryParticleLocatorBlock( submodule, viewmodule );
}
