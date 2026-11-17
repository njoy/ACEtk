// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/BremsstrahlungHighFrequencyBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapBremsstrahlungHighFrequencyBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::BremsstrahlungHighFrequencyBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "BremsstrahlungHighFrequencyBlock",
    "The electron HFB block with the bremsstrahlung high-frequency limit cross sections\n\n"
    "This block is part of the el format.\n\n"
    "The BremsstrahlungHighFrequencyBlock class contains 2 arrays of the\n"
    "same length:\n"
    "  - The energy points\n"
    "  - The cross section values\n\n"
    "The size NHFB of each (the total number of electron energy points) is\n"
    "stored in NXS(6)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ), python::arg( "cross_sections" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    energies          the energy values\n"
    "    cross_sections    the high-frequency-limit cross section values"
  )
  .def_property_readonly(

    "NHFB",
    &Block::NHFB,
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
  
    "cross_sections",
    [] (const Block& self ) -> DoubleRange
       { return self.crossSections(); },
    "The high-frequency-limit bremsstrahlung cross sections"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
