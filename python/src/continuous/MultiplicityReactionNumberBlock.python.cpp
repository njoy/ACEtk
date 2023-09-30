// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/MultiplicityReactionNumberBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapMultiplicityReactionNumberBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::MultiplicityReactionNumberBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "MultiplicityReactionNumberBlock",
    "The continuous energy YP block with the reaction MT numbers required for "
    "production cross section calculation\n\n"
    "The MultiplicityReactionNumberBlock class contains the reaction MT numbers\n"
    "that are needed in production cross section calculations using multiplicity\n"
    "values."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int > >(),
    python::arg( "reactions" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self         the block\n"
    "    reactions    the MT numbers"
  )
  .def_property_readonly(

    "NYP",
    &Block::NYP,
    "The number of available reactions"
  )
  .def_property_readonly(

    "number_reactions",
    &Block::numberReactions,
    "The number of available reactions"
  )
  .def(

    "MT",
    &Block::MT,
    python::arg( "index" ),
    "The reaction number for a reaction index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "reaction_number",
    &Block::reactionNumber,
    python::arg( "index" ),
    "The reaction number for a reaction index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "MTs",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.MTs(); },
    "The reaction numbers"
  )
  .def_property_readonly(

    "reaction_numbers",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.reactionNumbers(); },
    "The reaction numbers"
  )
  .def(

    "has_MT",
    &Block::hasMT,
    python::arg( "reaction" ),
    "Return whether or not the reaction number is present\n\n"
    "    self        the block\n"
    "    reaction    the reaction number"
  )
  .def(

    "has_reaction_number",
    &Block::hasReactionNumber,
    python::arg( "reaction" ),
    "Return whether or not the reaction number is present\n\n"
    "    self        the block\n"
    "    reaction    the reaction number"
  )
  .def(

    "index",
    &Block::index,
    python::arg( "reaction" ),
    "Return the index (one-based) of the reaction number\n\n"
    "    self        the block\n"
    "    reaction    the reaction number"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
