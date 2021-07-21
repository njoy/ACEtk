// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ReactionNumberBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapReactionNumberBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ReactionNumberBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ReactionNumberBlock",
    "The continuous energy MTR block with the reaction MT numbers\n\n"
    "The ReactionNumberBlock class contains the reaction MT numbers for all\n"
    "available reactions (excluding elastic)\n\n"
    "The number of available reactions (excluding elastic) is stored in NXS(4)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int >&& >(),
    python::arg( "mts" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self    the block\n"
    "    mts     the MT numbers"
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
  .def_property_readonly(

    "total_number_reactions",
    &Block::totalNumberReactions,
    "The total number of available reactions (including elastic)"
  )
  .def_property_readonly(

    "mts",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.mts(); },
    "The reaction numbers"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
