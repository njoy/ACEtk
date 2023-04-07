// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/TabulatedFissionMultiplicity.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapTabulatedFissionMultiplicity( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::TabulatedFissionMultiplicity;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TabulatedFissionMultiplicity",
    "Tabulated fission multiplicity\n\n"
    "The TabulatedFissionMultiplicity class contains the tabulated\n"
    "representation (LNU = 2) of the fission multiplicity. It is\n"
    "used in the NU block."
  );

  // wrap the block
  block
  .def_property_readonly(

    "LNU",
    &Block::LNU,
    "The representation type (should always be 2)"
  )
  .def_property_readonly(

    "type",
    &Block::type,
    "The representation type (should always be 2)"
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

    "NU",
    [] ( const Block& self ) -> DoubleRange
       { return self.NU(); },
    "The multiplicities"
  )
  .def_property_readonly(

    "multiplicities",
    [] ( const Block& self ) -> DoubleRange
       { return self.multiplicities(); },
    "The multiplicities"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
