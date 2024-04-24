// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/CrossSectionData.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapCrossSectionData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::CrossSectionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "CrossSectionData",
    "Convenience interface for cross section data from the SIG block"
  );

  // wrap the block
  block
  .def(

    python::init< std::size_t, std::vector< double > >(),
    python::arg( "index" ), python::arg( "values" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self      the block\n"
    "    index     the energy index\n"
    "    values    the cross section values"
  )
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

} // continuous namespace
