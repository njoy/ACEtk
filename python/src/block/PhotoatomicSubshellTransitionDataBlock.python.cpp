// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/PhotoatomicSubshellTransitionDataBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotoatomicSubshellTransitionDataBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotoatomicSubshellTransitionDataBlock;
  using PhotoatomicSubshellTransitionData = njoy::ACEtk::block::PhotoatomicSubshellTransitionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotoatomicSubshellTransitionDataBlock",
    "The photoatomic and electron RELO and XPROB block with the transition data\n\n"
    "The PhotoatomicSubshellTransitionDataBlock class contains the transition\n"
    "data for each subshell (the number of subshells NSSH is stored in NXS(7))."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< PhotoatomicSubshellTransitionData > >(),
    python::arg( "transitions" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self           the block\n"
    "    transitions    the transition data"
  )
  .def_property_readonly(

    "NSSH",
    &Block::NSSH,
    "The number of electron subshells"
  )
  .def_property_readonly(

    "number_electron_subshells",
    &Block::numberElectronSubshells,
    "The number of electron subshells"
  )
  .def(

    "LTRAN",
    &Block::LTRAN,
    python::arg( "index" ),
    "Return the relative transition data locator for a subshell index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "transition_data_locator",
    &Block::transitionDataLocator,
    python::arg( "index" ),
    "Return the relative transition data locator for a subshell index\n\n"
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

    "transition_data",
    &Block::transitionData,
    python::arg( "index" ),
    "Return the transition data for a subshell index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
