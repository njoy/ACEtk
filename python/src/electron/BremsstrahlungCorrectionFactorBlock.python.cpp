// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/BremsstrahlungCorrectionFactorBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapBremsstrahlungCorrectionFactorBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::BremsstrahlungCorrectionFactorBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "BremsstrahlungCorrectionFactorBlock",
    "The electron CRB block with the bremsstrahlung production correction factor data\n\n"
    "This block is part of the el format.\n\n"
    "The BremsstrahlungCorrectionFactorBlock class contains 2 arrays of the\n"
    "same length:\n"
    "  - The energy points\n"
    "  - The correction factor values\n\n"
    "The size NCRB of each (the total number of electron energy points) is\n"
    "stored in NXS(5)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ), python::arg( "corrections" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    energies       the energy values\n"
    "    corrections    the correction factor values"
  )
  .def_property_readonly(

    "NCRB",
    &Block::NCRB,
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
  
    "corrections",
    [] (const Block& self ) -> DoubleRange
       { return self.corrections(); },
    "The bremsstrahlung production correction factors"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
