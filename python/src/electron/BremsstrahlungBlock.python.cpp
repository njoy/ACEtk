// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/BremsstrahlungBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapBremsstrahlungBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::BremsstrahlungBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "BremsstrahlungBlock",
    "The photoatomic BREML block with the average electron energy after Bremsstrahlung\n\n"
    "This block is part of the eprdata formats.\n\n"
    "The BremsstrahlungBlock class contains 2 arrays of the same\n"
    "length:\n"
    "  - the energy points\n"
    "  - the average energy remaining after Bremsstrahlung\n\n"
    "The size NBL of each (the total number of energy points) is stored in NXS(12)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ), python::arg( "remaining" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self         the block\n"
    "    energies     the energy values\n"
    "    remaining    the average energy remaining after Bremsstrahlung"
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
    "The average energy remaining after Bremsstrahlung"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
