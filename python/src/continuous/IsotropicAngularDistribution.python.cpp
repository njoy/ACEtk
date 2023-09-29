// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/IsotropicAngularDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapIsotropicAngularDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::IsotropicAngularDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "IsotropicAngularDistribution",
    "Isotropic angular distribution\n\n"
    "The IsotropicAngularDistribution class contains contains no data other than\n"
    "the incident energy. It is a convenience interface object used in the AND block"
  );

  // wrap the block
  block
  .def(

    python::init< double >(),
    python::arg( "energy" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self      the block\n"
    "    energy    the associated energy value\n"
  )
  .def_property_readonly(

    "energy",
    &Block::energy,
    "The associated energy value"
  );
}

} // continuous namespace
