// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/IsotropicAngularDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapIsotropicAngularDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::IsotropicAngularDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "IsotropicAngularDistribution",
    "Convenience interface for an isotropic angular distribution from the "
    "AND block"
  );

  // wrap the block
  block
  .def(

    python::init< double >(),
    python::arg( "incident" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    incident    the incident energy value\n"
  )
  .def_property_readonly(

    "incident_energy",
    &Block::incidentEnergy,
    "The incident energy"
  );
}

} // block namespace
