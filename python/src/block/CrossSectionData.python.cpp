// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/CrossSectionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapCrossSectionData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::CrossSectionBlock::CrossSectionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "CrossSectionData",
    "Convenience interface for cross section data from the SIG block"
  );

  // wrap the block
  block
  .def_property_readonly(

    "energy_index",
    &Block::energyIndex,
    "The energy index"
  )
  .def_property_readonly(

    "number_values",
    &Block::numberValues,
    "The number of cross section values"
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

} // block namespace
