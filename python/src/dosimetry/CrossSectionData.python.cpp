// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/dosimetry/CrossSectionData.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace dosimetry {

void wrapCrossSectionData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::dosimetry::CrossSectionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "CrossSectionData",
    "Cross section data from the SIGD block for a single reaction\n\n"
    "The CrossSectionData class contains the interpolation regions (if any are\n"
    "defined) along with the energy and cross section values. The dosimetry cross\n"
    "sections are different from the other cross section data blocks in that the\n"
    "data is not given on a common energy grid."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ), python::arg( "xs" ),
    "Initialise the block assuming linear interpolation\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    energies    the energy values\n"
    "    xs          the xs values"
  )
  .def(

    python::init< std::vector< long >, std::vector< long >,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "xs" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self            the block\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    xs              the xs values"
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

    "cross_sections",
    [] ( const Block& self ) -> DoubleRange
       { return self.crossSections(); },
    "The cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // dosimetry namespace
