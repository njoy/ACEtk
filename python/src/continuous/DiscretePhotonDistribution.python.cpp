// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/DiscretePhotonDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapDiscretePhotonDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::DiscretePhotonDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "DiscretePhotonDistribution",
    "The DiscretePhotonDistribution class contains the photon energy if the\n"
    "photon is a primary photon or the binding energy when the photon is not a\n"
    "primary photon. It is used in the DLW block as ACE LAW 2."
  );

  // wrap the block
  block
  .def(

    python::init< double, double, unsigned int, double >(),
    python::arg( "emin" ), python::arg( "emax" ),
    python::arg( "lp" ), python::arg( "energy" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self      the block\n"
    "    emin      the minimum energy for the distribution\n"
    "    emax      the maximum energy for the distribution\n"
    "    lp        the primary photon flag (0, 1 or 2)\n"
    "    energy    the photon or binding energy"
  )
  .def_property_readonly(

    "LAW",
    [] ( const Block& self ) { return self.LAW(); },
    "The distribution type"
  )
  .def_property_readonly(

    "type",
    [] ( const Block& self ) { return self.type(); },
    "The distribution type"
  )
  .def_property_readonly(

    "minimum_incident_energy",
    &Block::minimumIncidentEnergy,
    "The minimum incident energy for the distribution"
  )
  .def_property_readonly(

    "maximum_incident_energy",
    &Block::maximumIncidentEnergy,
    "The maximum incident energy for the distribution"
  )
  .def_property_readonly(

    "LP",
    &Block::LP,
    "The primary flag value (0, 1 or 2)"
  )
  .def_property_readonly(

    "primary_photon_flag",
    &Block::primaryPhotonFlag,
    "The primary flag value (0, 1 or 2)"
  )
  .def_property_readonly(

    "is_primary_photon",
    &Block::isPrimaryPhoton,
    "Indicates whether or not the photon is a primary photon"
  )
  .def_property_readonly(

    "EG",
    &Block::EG,
    "The photon or binding energy"
  )
  .def_property_readonly(

    "photon_or_binding_energy",
    &Block::photonOrBindingEnergy,
    "The photon or binding energy"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
