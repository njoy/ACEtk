// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/ExcitationBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapExcitationBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::ExcitationBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ExcitationBlock",
    "The photoatomic EXCIT block with the electron excitation energy loss data\n\n"
    "This block is part of the eprdata formats.\n\n"
    "The ExcitationBlock class contains 2 arrays of the same\n"
    "length:\n"
    "  - the energy points\n"
    "  - the average excitation energy loss values\n\n"
    "The size NXL of each (the total number of excitation energy points) is\n"
    "stored in NXS(9)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ), python::arg( "loss" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    energies    the energy values\n"
    "    loss        the average excitation energy loss values"
  )
  .def_property_readonly(

    "NXL",
    &Block::NXL,
    "The number of energy points"
  )
  .def_property_readonly(

    "number_energy_points",
    &Block::numberEnergyPoints,
    "The number of energy points"
  )
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "excitation_energy_loss",
    [] ( const Block& self ) -> DoubleRange
       { return self.excitationEnergyLoss(); },
    "The average excitation energy loss values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
