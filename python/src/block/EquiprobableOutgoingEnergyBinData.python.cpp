// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/EquiprobableOutgoingEnergyBinData.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapEquiprobableOutgoingEnergyBinData( python::module& module,
                                            python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::EquiprobableOutgoingEnergyBinData;
  using Distribution = njoy::ACEtk::block::EquiprobableOutgoingEnergyBins;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EquiprobableOutgoingEnergyBinData",
    "Equiprobable outgoing energy bin data\n\n"
    "The EquiprobableOutgoingEnergyBinData class contains the equiprobable bins\n"
    "for a set of incident energy values. It is used in the AND block. This\n"
    "format is only used in old ACE data."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< Distribution > >(),
    python::arg( "distributions" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    distributions    the distributions for each incident energy"
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

    "interpolation_data",
    &Block::interpolationData,
    "The interpolation data"
  )
  .def_property_readonly(

    "NB",
    &Block::NB,
    "The number of interpolation regions"
  )
  .def_property_readonly(

    "number_interpolation_regions",
    &Block::numberInterpolationRegions,
    "The number of interpolation regions"
  )
  .def_property_readonly(

    "NBT",
    [] ( const Block& self ) -> LongRange
       { return self.NBT(); },
    "The interpolation boundaries"
  )
  .def_property_readonly(

    "boundaries",
    [] ( const Block& self ) -> LongRange
       { return self.boundaries(); },
    "The interpolation boundaries"
  )
  .def_property_readonly(

    "INT",
    [] ( const Block& self ) -> LongRange
       { return self.INT(); },
    "The interpolation type for each range"
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Block& self ) -> LongRange
       { return self.interpolants(); },
    "The interpolation type for each range"
  )
  .def_property_readonly(

    "NE",
    &Block::NE,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "number_incident_energies",
    &Block::numberIncidentEnergies,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "incident_energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.incidentEnergies(); },
    "The incident energy values"
  )
  .def(

    "incident_energy",
    &Block::incidentEnergy,
    python::arg( "index" ),
    "Return the incident energy for a given index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
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

    "NET",
    &Block::NET,
    "The number of outgoing energy values for each incident energy"
  )
  .def_property_readonly(

    "number_bins",
    &Block::numberBins,
    "The number of equiprobable outgoing energy bins"
  )
  .def(

    "distribution",
    &Block::distribution,
    python::arg( "index" ),
    "Return the outgoing energy bin values for an incident energy index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
