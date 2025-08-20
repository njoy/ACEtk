// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/BremsstrahlungEnergySpectrumBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapBremsstrahlungEnergySpectrumBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::BremsstrahlungEnergySpectrumBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "BremsstrahlungEnergySpectrumBlock",
    "The electron RKT block with the bremsstrahlung energy spectrum data\n\n"
    "This block is part of the el03 format.\n\n"
    "The BremsstrahlungEnergySpectrumBlock class contains 1 array with\n"
    "the ratio values of photon energy over electron energy for the\n"
    "bremsstrahlung energy spectrum calculation (NEL == 3).\n\n"
    "The size NRKT is stored in NXS(9)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "energy_ratios" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    energy_ratios    the photon energy ratios"
  )
  .def_property_readonly(

    "NRKT",
    &Block::NRKT,
    "The number of bremstrahlung energy spectrum points"
  )
  .def_property_readonly(

    "number_photon_energy_ratios",
    &Block::numberPhotonEnergyRatios,
    "The number of bremstrahlung energy spectrum points"
  )
  .def_property_readonly(
  
    "photon_energy_ratios",
    [] ( const Block& self ) -> DoubleRange
       { return self.photonEnergyRatios(); },
    "The energy points for bremstrahlung energy spectrum interpolation"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
