// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/AngularDistributionType.hpp"

// namespace aliases
namespace python = pybind11;

void wrapAngularDistributionType( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ACEtk::AngularDistributionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "AngularDistributionType",
    "The angular distribution types",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Isotropic", Component::Isotropic )
  .value( "Equiprobable", Component::Equiprobable )
  .value( "Tabulated", Component::Tabulated );
}
