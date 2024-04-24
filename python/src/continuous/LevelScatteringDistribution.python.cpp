// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/LevelScatteringDistribution.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapLevelScatteringDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::LevelScatteringDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "LevelScatteringDistribution",
    "The energy distribution uses analytical level scattering\n\n"
    "The LevelScatteringDistribution class contains two parameter values that\n"
    "determine the level scattering distribution (in the centre of mass):\n"
    "  Eprime = C2 * ( E - C1 )\n"
    "with:\n"
    "  C1 = ( A + 1 ) / A * abs( Q )\n"
    "  C2 = ( A / ( A + 1 ) )^2\n"
    "It is used in the DLW block as ACE LAW 3."
  );

  // wrap the block
  block
  .def(

    python::init< double, double, double, double >(),
    python::arg( "emin" ), python::arg( "emax" ),
    python::arg( "c1" ), python::arg( "c2" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self    the block\n"
    "    emin    the minimum energy for the distribution\n"
    "    emax    the maximum energy for the distribution\n"
    "    c1      the value of C1 = ( A + 1 ) / A * abs( Q )\n"
    "    c2      the value of C2 = ( A / ( A + 1 ) )^2"
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

    "C1",
    &Block::C1,
    "The value of C1 = ( A + 1 ) / A * abs( Q )"
  )
  .def_property_readonly(

    "C2",
    &Block::C2,
    "The value of C2 = ( A / ( A + 1 ) )^2"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
