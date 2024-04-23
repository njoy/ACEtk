// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/SubshellTransitionDataBlock.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapSubshellTransitionDataBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::SubshellTransitionDataBlock;
  using SubshellTransitionData = njoy::ACEtk::electron::SubshellTransitionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SubshellTransitionDataBlock",
    "The electron RELO and XPROB block with the transition data\n\n"
    "The SubshellTransitionDataBlock class contains the transition data for each\n"
    "subshell (the number of subshells NSSH is stored in NXS(7))."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< SubshellTransitionData > >(),
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

} // electron namespace
