// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/DistributionProbability.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapDistributionProbability( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::DistributionProbability;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "DistributionProbability",
    "The probability for a distribution to occur"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ), python::arg( "probabilities" ),
    "Initialise the block assuming linear interpolation\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    energies         the energy values\n"
    "    probabilities    the probability values"
  )
  .def(

    python::init< std::vector< long >, std::vector< long >,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "probabilities" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self            the block\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    probabilities   the probability values"
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
    "The number of energy values"
  )
  .def_property_readonly(

    "number_energy_points",
    &Block::numberEnergyPoints,
    "The number of energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "probabilities",
    [] ( const Block& self ) -> DoubleRange
       { return self.probabilities(); },
    "The probability values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
