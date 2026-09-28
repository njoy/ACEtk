// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electroatomic/BremsstrahlungBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electroatomic {

void wrapBremsstrahlungBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electroatomic::BremsstrahlungBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "BremsstrahlungBlock",
    "The electron BREML block with the average electron energy after Bremsstrahlung\n\n"
    "This block is part of the eprdata formats.\n\n"
    "The BremsstrahlungBlock class contains 2 arrays of the same length:\n"
    "  - the energy points\n"
    "  - the average energy remaining after Bremsstrahlung\n\n"
    "For NEPR = 3, the second array contains the average energy loss instead.\n\n"
    "The size NBL of each (the total number of energy points) is stored in NXS(12)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double >, unsigned int >(),
    python::arg( "energies" ), python::arg( "remaining" ), python::arg( "nepr" ) = 1,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self         the block\n"
    "    energies     the energy values\n"
    "    remaining    the average energy remaining after Bremsstrahlung\n"
    "                 (or the average energy loss when NEPR = 3)\n"
    "    nepr         1 for remaining energy, 3 for energy loss"
  )
  .def_property_readonly(

    "NBL",
    &Block::NBL,
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

    "energy_after_bremsstrahlung",
    [] ( const Block& self ) -> DoubleRange
       { return self.energyAfterBremsstrahlung(); },
    "The average energy remaining after Bremsstrahlung\n\n"
    "Requires NEPR = 1."
  )
  .def_property_readonly(

    "energy_loss",
    [] ( const Block& self ) -> DoubleRange
       { return self.energyLoss(); },
    "The average energy loss (requires NEPR = 3)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electroatomic namespace
