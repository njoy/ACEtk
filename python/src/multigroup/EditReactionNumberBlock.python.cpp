// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/EditReactionNumberBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapEditReactionNumberBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::EditReactionNumberBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EditReactionNumberBlock",
    "The multigroup MTED block with the edit reaction MT numbers\n\n"
    "The EditReactionNumberBlock class contains the edit reaction MT numbers\n\n"
    "The number of edit reactions is stored in NXS(4).\n\n"
    "Parameters\n"
    "----------\n"
    "    edit_reaction_numbers : list of int \n "
    "        the edit reaction MT numbers\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int > >(),
    python::arg( "edit_reaction_numbers" ),
    "Create the MTED block with the edit reaction MT numbers\n\n"
    
  )
  .def_property_readonly(

    "NEDIT",
    &Block::NEDIT,
    "The number of edit reactions "
  )
  .def_property_readonly(

    "number_edit_reactions",
    &Block::numberEditReactions,
    "The number of edit reactions"
  )
  .def(

    "MT",
    &Block::MT,
    python::arg( "index" ),
    "The edit reaction number for an index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int   \n"
    "        the index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The edit reaction number at the index given\n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        If the index provided doesn't exist in the block \n\n"
  )
  .def(

    "edit_reaction_number",
    &Block::editReactionNumber,
    python::arg( "index" ),
    "The edit reaction number for an index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int   \n"
    "        the index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The edit reaction number at the index given\n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        If the index provided doesn't exist in the block \n\n"
  )
  .def_property_readonly(

    "MTs",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.MTs(); },
    "The edit reaction numbers"
  )
  .def_property_readonly(

    "edit_reaction_numbers",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.editReactionNumbers(); },
    "The edit reaction numbers"
  )
  .def(

    "has_MT",
    &Block::hasMT,
    python::arg( "mt" ),
    "Return whether or not a reaction MT is present in the edit reactions\n\n"
    "Parameters\n"
    "----------\n"
    "    mt : int   \n"
    "        the mt number\n\n"
    "Returns\n"
    "-------\n"
    "    bool \n"
    "        True if the MT exists in the edit reactions\n\n"
  )
  .def(

    "has_edit_reaction_number",
    &Block::hasEditReactionNumber,
    python::arg( "reaction" ),
    "Return whether or not a reaction MT is present in the edit reactions\n\n"
    "Parameters\n"
    "----------\n"
    "    mt : int   \n"
    "        the mt number\n\n"
    "Returns\n"
    "-------\n"
    "    bool \n"
    "        True if the MT exists in the edit reactions\n\n"
  )
  .def(

    "index",
    &Block::index,
    python::arg( "mt" ),
    "Return the index (one-based) of the edit reaction number, if present\n\n"
    "Parameters\n"
    "----------\n"
    "    mt : int   \n"
    "        the mt number\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The index of the MT number\n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        If the MT provided doesn't exist in the block \n\n"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
