// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/ReferenceFrame.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReferenceFrame( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ACEtk::ReferenceFrame;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "ReferenceFrame",
    "The reference frame for the angular and energy distributions",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "CentreOfMass", Component::CentreOfMass )
  .value( "Laboratory", Component::Laboratory );
}
