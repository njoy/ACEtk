// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/NBodyPhaseSpaceDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapNBodyPhaseSpaceDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::NBodyPhaseSpaceDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "NBodyPhaseSpaceDistribution",
    "The energy distribution uses the N-body phase space formalism\n\n"
    "The NBodyPhaseSpaceDistribution class contains two parameter values that\n"
    "determine the distribution: the number of particles in the system and the\n"
    "total mass ratio."
  );

  // wrap the block
  block
  .def(

    python::init< double, double, unsigned int, double >(),
    python::arg( "emin" ), python::arg( "emax" ),
    python::arg( "npsx" ), python::arg( "ap" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self    the block\n"
    "    emin    the minimum energy for the distribution\n"
    "    emax    the maximum energy for the distribution\n"
    "    npsx    the number of particles in the system\n"
    "    ap      the total mass ratio"
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

    "NPSX",
    &Block::NPSX,
    "The number of particles in the system"
  )
  .def_property_readonly(

    "number_particles",
    &Block::numberParticles,
    "The number of particles in the system"
  )
  .def_property_readonly(

    "AP",
    &Block::AP,
    "The total mass ratio"
  )
  .def_property_readonly(

    "total_mass_ratio",
    &Block::totalMassRatio,
    "The total mass ratio"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
