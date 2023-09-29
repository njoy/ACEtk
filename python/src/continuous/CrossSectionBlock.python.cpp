// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/CrossSectionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapCrossSectionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::CrossSectionBlock;
  using CrossSectionData = njoy::ACEtk::block::CrossSectionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "CrossSectionBlock",
    "The continuous energy LSIG and SIG block with the cross section data\n\n"
    "The CrossSectionBlock class contains NXS(4) sets of cross section values,\n"
    "one for each reaction number on the MTR block. The order of these cross\n"
    "section data sets is the same as the order of the reaction numbers in the\n"
    "MTR block."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< CrossSectionData > >(),
    python::arg( "xs" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self    the block\n"
    "    xs      the cross section data"
  )
  .def_property_readonly(

    "NTR",
    &Block::NTR,
    "The number of available reactions (excluding elastic)"
  )
  .def_property_readonly(

    "number_reactions",
    &Block::numberReactions,
    "The number of available reactions (excluding elastic)"
  )
  .def(

    "LSIG",
    &Block::LSIG,
    python::arg( "index" ),
    "Return the relative cross section locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "cross_section_locator",
    &Block::crossSectionLocator,
    python::arg( "index" ),
    "Return the relative cross section locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "data",
    &Block::data,
    "The cross section data"
  )
  .def(

    "cross_section_data",
    &Block::crossSectionData,
    python::arg( "index" ),
    "Return the cross section data for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "energy_index",
    &Block::energyIndex,
    python::arg( "index" ),
    "Return the energy index for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "number_values",
    &Block::numberValues,
    python::arg( "index" ),
    "Return the number of cross section values for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "cross_sections",
    [] ( const Block& self, std::size_t index ) -> DoubleRange
       { return self.crossSections( index ); },
    python::arg( "index" ),
    "Return the cross section values for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
