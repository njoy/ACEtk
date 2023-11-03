// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/TwoBodyTransferDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapTwoBodyTransferDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::TwoBodyTransferDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TwoBodyTransferDistribution",
    "The energy distribution uses two body transfer\n\n"
    "It is used in the DLW block as ACE LAW 33."
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
    "    c1      the value of C1\n"
    "    c2      the value of C2"
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
    "The value of C1"
  )
  .def_property_readonly(

    "C2",
    &Block::C2,
    "The value of C2"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
