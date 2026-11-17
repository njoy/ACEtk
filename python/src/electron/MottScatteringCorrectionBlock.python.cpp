// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/MottScatteringCorrectionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapMottScatteringCorrectionBlock( python::module& module, python::module& ) {
  
  // type aliases
  using Block = njoy::ACEtk::electron::MottScatteringCorrectionBlock;
  
  // wrap views created by this block
  
  // create the block
  python::class_< Block > block(
  
    module,
    "MottScatteringCorrectionBlock",
    "The electron MOT block with the Mott scattering correction data\n\n"
    "This block is part of el and el03 formats.\n\n"
    "The MottScatteringCorrectionBlock class contains 6 arrays of the same\n"
    "length:\n"
    "  - The energy points\n"
    "  - The Mott scattering correction h(theta) for theta = 0\n"
    "  - The Mott scattering correction h(theta) for theta = pi/4\n"
    "  - The Mott scattering correction h(theta) for theta = pi/2\n"
    "  - The Mott scattering correction h(theta) for theta = 3*pi/4\n"
    "  - The Mott scattering correction h(theta) for theta = pi\n\n"
    "The size NMOT of each (the total number of Mott scattering cross\n"
    "section energy points) is stored in NXS(4)."
  );
  
  // wrap the block
  block
  .def(
  
    python::init< std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ), python::arg( "corrections0deg" ),
    python::arg( "corrections45deg" ), python::arg( "corrections90deg" ),
    python::arg( "corrections135deg" ), python::arg( "corrections180deg" ),
    "Initialize the block\n\n"
    "Arguments:\n"
    "    energies             the energy values\n"
    "    corrections0deg      the Mott scattering corrections at 0 degrees\n"
    "    corrections45deg     the Mott scattering corrections at 45 degrees\n"
    "    corrections90deg     the Mott scattering corrections at 90 degrees\n"
    "    corrections135deg    the Mott scattering corrections at 135 degrees\n"
    "    corrections180deg    the Mott scattering corrections at 180 degrees"
  )
  .def_property_readonly(
  
    "NMOT",
    &Block::NMOT,
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
    "The energy points"
  )
  .def(
  
    "mott_scattering_correction",
    [] ( const Block& self, std::size_t index ) -> DoubleRange
       { return self.mottScatteringCorrection( index ); },
    python::arg( "index" ),
    "The Mott scattering correction for an index.\n\n"
    "Arguments:\n"
    "    index   the index (1 to 5 inclusively, one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
