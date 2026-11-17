// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/NumberSecondaryAngularVariablesBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapNumberSecondaryAngularVariablesBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::NumberSecondaryAngularVariablesBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "NumberSecondaryAngularVariablesBlock",
    "The multigroup NLEG2 block with the number of angular distribution variables\n\n"
    "The number of secondary particle numbers (NSEC) is stored in NXS(8).\n\n"
    "Parameters\n"
    "----------\n"
    "    numbers : list of int \n"
    "        the number of variables for each particle \n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int > >(),
    python::arg( "numbers" ),
    "Create the NLEG2 block\n\n"
  )
  .def_property_readonly(

    "NSEC",
    &Block::NSEC,
    "The number of secondary particles"
  )
  .def_property_readonly(

    "number_secondary_particles",
    &Block::numberSecondaryParticles,
    "The number of secondary particles"
  )
  .def(

    "NLEG2",
    &Block::NLEG2,
    python::arg( "index" ),
    "The number of angular distribution variables for a secondary particle index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int \n"
    "        the index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The number of angular distribution variables \n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        When the index is out of range \n\n"
  )
  .def(

    "number_angular_distribution_variables",
    &Block::numberAngularDistributionVariables,
    python::arg( "index" ),
    "The number of angular distribution variables for a secondary particle index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int \n"
    "        the index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The number of angular distribution variables \n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        When the index is out of range \n\n"
  )
  .def_property_readonly(

    "NLEG2s",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.NLEG2s(); },
    "The list of number of angular distribution variables"
  )
  .def_property_readonly(

    "number_angular_distribution_variables_list",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.numberAngularDistributionVariablesList(); },
    "The list of number of angular distribution variables"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
