// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/StoppingPowerBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapStoppingPowerBlock( python::module& module,
                                          python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::StoppingPowerBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "StoppingPowerBlock",
    "The multigroup stopping power section block\n\n"
    " The StoppingPowerBlock class contains 1 array: \n"
    "   - the stopping power for each group \n"
    " The size the array (the total number of energy groups) is stored in NXS(5). \n\n"
    "Parameters\n"
    "----------\n"
    "    stopping_power : list of float \n "
    "        the stopping power for each group\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "stopping_power" ),
    "Create the STOP block with the stopping power values \n\n"
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

    "SPOW",
    [] ( const Block& self ) -> DoubleRange
       { return self.SPOW(); },
    "The stopping power values"
  )
  .def_property_readonly(

    "stopping_power",
    [] ( const Block& self ) -> DoubleRange
       { return self.stoppingPower(); },
    "The stopping power values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
