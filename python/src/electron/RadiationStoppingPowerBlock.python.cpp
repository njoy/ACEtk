// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/RadiationStoppingPowerBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapRadiationStoppingPowerBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::RadiationStoppingPowerBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "RadiationStoppingPowerBlock",
    "The electron RAD block with the radiation stopping power data\n\n"
    "This block is part of el and el03 formats.\n\n"
    "The RadiationStoppingPowerBlock class contains 3 arrays of the same\n"
    "length:\n"
    "  - The energy points\n"
    "  - The normalized stopping powers\n"
    "  - The electron-electron bremsstrahlung correction (NEL == 3)\n\n"
    "The size NRAD of each (the total number of electron energy points) is\n"
    "stored in NXS(3)."
  );
  
  // wrap the block
  block
  .def(
  
    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ),
    python::arg( "stopping_powers" ),
    "Initialize the block\n\n"
    "Arguments:\n"
    "    self               the block\n"
    "    energies           the energy values\n"
    "    stopping_powers    the normalized radiative stopping power values\n"
    "    corrections        the electron-electron bremsstrahlung correction values (NEL == 3)\n"
  )
  .def(
  
    python::init< std::vector< double >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "energies" ),
    python::arg( "stopping_powers" ),
    python::arg( "corrections" ),
    "Initialize the block\n\n"
    "Arguments:\n"
    "    self               the block\n"
    "    energies           the energy values\n"
    "    stopping_powers    the normalized radiative stopping power values\n"
    "    corrections        the electron-electron bremsstrahlung correction values (NEL == 3)\n"
  )
  .def_property_readonly(
  
    "NRAD",
    &Block::NRAD,
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
    "The energy points for radiation stopping power interpolation"
  )
  .def_property_readonly(
  
    "stopping_powers",
    [] ( const Block& self ) -> DoubleRange
       { return self.stoppingPowers(); },
    "The normalized radiation stopping powers"
  )
  .def_property_readonly(
  
    "corrections",
    [] ( const Block& self ) -> std::optional< DoubleRange >
       { return self.corrections(); },
    "The electron-electron bremsstrahlung correction factors (NEL == 3)"
  );
  
  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

}  // electron namespace
