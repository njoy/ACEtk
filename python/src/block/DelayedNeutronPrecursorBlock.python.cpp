// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/DelayedNeutronPrecursorBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapDelayedNeutronPrecursorBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::DelayedNeutronPrecursorBlock;
  using DelayedNeutronPrecursorData = njoy::ACEtk::block::DelayedNeutronPrecursorData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "DelayedNeutronPrecursorBlock",
    "The continuous energy BDD block with the delayed neutron precursor data\n\n"
    "The number of precursor groups is stored in NXS(8)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< DelayedNeutronPrecursorData > >(),
    python::arg( "groups" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self      the block\n"
    "    groups    the cross section data"
  )
  .def_property_readonly(

    "NPCR",
    &Block::NPCR,
    "The number of delayed neutron precursor groups"
  )
  .def_property_readonly(

    "number_delayed_precursors",
    &Block::numberDelayedPrecursors,
    "The number of delayed neutron precursor groups"
  )
  .def_property_readonly(

    "data",
    &Block::data,
    "The delayed neutron precursor data"
  )
  .def(

    "precursor_group_data",
    &Block::precursorGroupData,
    python::arg( "index" ),
    "Return the precursor data for a group index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
