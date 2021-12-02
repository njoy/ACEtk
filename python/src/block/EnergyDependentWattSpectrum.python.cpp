// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/EnergyDependentWattSpectrum.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapEnergyDependentWattSpectrum( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::EnergyDependentWattSpectrum;
  using ParameterData = njoy::ACEtk::block::ParameterData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EnergyDependentWattSpectrum",
    "An energy dependent Watt spectrum\n\n"
    "The EnergyDependentWattSpectrum class contains the tabulated values for the\n"
    "energy dependent a and b parameters as well as the restriction energy U used\n"
    "to describe the Watt spectrum. It is used in the DLW block as ACE LAW 11."
  );

  // wrap the block
  block
  .def(

    python::init( [] ( ParameterData a, ParameterData b, double energy )
                     { return Block( std::move( a ), std::move( b ), energy ); } ),
    python::arg( "a" ), python::arg( "b" ), python::arg( "energy" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self      the block\n"
    "    a         the data for parameter a\n"
    "    b         the data for parameter b\n"
    "    energy    the restriction energy"
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

    "a",
    &Block::a,
    "The data for parameter a"
  )
  .def_property_readonly(

    "b",
    &Block::b,
    "The data for parameter b"
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

    "U",
    &Block::U,
    "The restriction energy"
  )
  .def_property_readonly(

    "restriction_energy",
    &Block::restrictionEnergy,
    "The restriction energy"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
