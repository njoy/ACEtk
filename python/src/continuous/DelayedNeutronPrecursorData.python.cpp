// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/DelayedNeutronPrecursorData.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapDelayedNeutronPrecursorData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::DelayedNeutronPrecursorData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "DelayedNeutronPrecursorData",
    "Delayed neutron precursor group data\n\n"
    "The DelayedNeutronPrecursorData class contains the precursor group's decay\n"
    "constant and the associated probability as a function of incident energy."
  );

  // wrap the block
  block
  .def(

    python::init< unsigned int, double,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "number" ), python::arg( "constant" ),
    python::arg( "energies" ), python::arg( "probabilities" ),
    "Initialise the block assuming linear interpolation\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    number           the precursor group number\n"
    "    constant         the precursor group's decay constant\n"
    "    energies         the energy values\n"
    "    probabilities    the probability values"
  )
  .def(

    python::init< unsigned int, double,
                  std::vector< long >, std::vector< long >,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "number" ), python::arg( "constant" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "probabilities" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    number           the precursor group number\n"
    "    constant         the precursor group's decay constant\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    energies         the energy values\n"
    "    probabilities    the probability values"
  )
  .def_property_readonly(

    "number",
    &Block::number,
    "The precursor group number"
  )
  .def_property_readonly(

    "DEC",
    &Block::DEC,
    "The precursor group's decay constant"
  )
  .def_property_readonly(

    "decay_constant",
    &Block::decayConstant,
    "The precursor group's decay constant"
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
    "The interpolants"
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Block& self ) -> LongRange
       { return self.interpolants(); },
    "The interpolants"
  )
  .def_property_readonly(

    "NE",
    &Block::NE,
    "The number of values"
  )
  .def_property_readonly(

    "number_values",
    &Block::numberValues,
    "The number of values"
  )
  .def_property_readonly(

    "E",
    [] ( const Block& self ) -> DoubleRange
       { return self.E(); },
    "The energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "P",
    [] ( const Block& self ) -> DoubleRange
       { return self.P(); },
    "The probabilities"
  )
  .def_property_readonly(

    "probabilities",
    [] ( const Block& self ) -> DoubleRange
       { return self.probabilities(); },
    "The probabilities"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
