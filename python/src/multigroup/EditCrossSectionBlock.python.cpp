// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/EditCrossSectionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapEditCrossSectionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::EditCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EditCrossSectionBlock",
    "The EditCrossSectionBlock class contains the edit cross section values \n"
    "in the XSED block. The number of edit reactions is in NXS(4) and the \n"
    "number of groups is NXS(5). The order of the edit cross sections is the \n"
    "same as the order of the edit reaction numbers in the MTED block. \n\n"
    "Parameters\n"
    "----------\n"
    "    reactions : list of lists of float \n"
    "        The edit reaction cross section data \n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< std::vector< double > > >(),
    python::arg( "reactions" ),
    "Create the XSED block with the edit cross section values \n\n"
  )  
  .def_property_readonly(

    "NGRP",
    &Block::NGRP,
    "The number of energy groups"
  )
  .def_property_readonly(

    "number_energy_groups",
    &Block::numberEnergyGroups,
    "The number of energy groups"
  )
  .def_property_readonly(

    "NEDIT",
    &Block::NEDIT,
    "The number of edit reactions"
  )
  .def_property_readonly(

    "number_edit_reactions",
    &Block::numberEditReactions,
    "The number of edit reactions"
  )
  .def(

    "XS",
    [] ( const Block& self, unsigned int index ) -> DoubleRange
       { return self.XS( index ); },
    python::arg( "index" ),
    "Return the cross section at a specific index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int \n"
    "        The edit reaction index \n\n"
    "Returns\n"
    "-------\n"
    "    list of floats \n"
    "        The cross section values for the edit reaction \n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        When the index is out of range \n\n"
  )
  .def(

    "edit_cross_section",
    [] ( const Block& self, unsigned int index ) -> DoubleRange
       { return self.editCrossSection( index ); },
    python::arg( "index" ),
    "Return the cross section at a specific index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int \n"
    "        The edit reaction index \n\n"
    "Returns\n"
    "-------\n"
    "    list of floats \n"
    "        The cross section values for the edit reaction \n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        When the index is out of range \n\n"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
