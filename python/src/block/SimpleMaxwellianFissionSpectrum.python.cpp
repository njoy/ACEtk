// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/SimpleMaxwellianFissionSpectrum.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapSimpleMaxwellianFissionSpectrum( python::module& module,
                                          python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::SimpleMaxwellianFissionSpectrum;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SimpleMaxwellianFissionSpectrum",
    "Convenience interface for outgoing energy distribution data from the\n"
    "DLW block for a single reaction using a simple Maxwellian fission spectrum"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  double >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "temperatures" ),
    python::arg( "energy" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self            the block\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    temperatures    the temperature values\n"
    "    energy          the restriction energy"
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

    "number_energy_points",
    &Block::numberEnergyPoints,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "temperatures",
    [] ( const Block& self ) -> DoubleRange
       { return self.temperatures(); },
    "The temperature values"
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
