// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/MomentumTransferBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapMomentumTransferBlock( python::module& module,
                                          python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::MomentumTransferBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "MomentumTransferBlock",
    "The multigroup momentum transfer block\n\n"
    " The MomentumTransferBlock class contains 1 array: \n"
    "   - the momentum transfer values for each group \n"
    " The size the array (the total number of energy groups) is stored in NXS(5). \n\n"
    "Parameters\n"
    "----------\n"
    "    momentum_transfer : list of float \n "
    "        the momentum transfer values for each group\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "momentum_transfer" ),
    "Create the MOM block with the momentum transfer values \n\n"
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

    "MOMTR",
    [] ( const Block& self ) -> DoubleRange
       { return self.MOMTR(); },
    "The momentum transfer values"
  )
  .def_property_readonly(

    "momentum_transfer",
    [] ( const Block& self ) -> DoubleRange
       { return self.momentumTransfer(); },
    "The momentum transfer values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
