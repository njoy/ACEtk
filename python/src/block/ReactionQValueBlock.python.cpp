// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ReactionQValueBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapReactionQValueBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ReactionQValueBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ReactionQValueBlock",
    "The continuous energy LQR block with the reaction Q values\n\n"
    "The ReactionQValueBlock class contains the reaction Q values for all\n"
    "available reactions (excluding elastic). The order of these Q values\n"
    "is the same as the order of the reaction numbers in the MTR block.\n\n"
    "The number of available reactions (excluding elastic) is stored in NXS(4)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >&& >(),
    python::arg( "reactions" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self         the block\n"
    "    reactions    the MT numbers"
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

    "QValue",
    &Block::QValue,
    python::arg( "index" ),
    "The reaction Q value for a reaction index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "QValues",
    [] ( const Block& self ) -> DoubleRange
       { return self.QValues(); },
    "The reaction Q values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
