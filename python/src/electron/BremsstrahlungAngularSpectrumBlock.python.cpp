// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/BremsstrahlungAngularSpectrumBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapBremsstrahlungAngularSpectrumBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::BremsstrahlungAngularSpectrumBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "BremsstrahlungAngularSpectrumBlock",
    "The electron RKA block with the bremsstrahlung angular spectrum data\n\n"
    "This block is part of the el03 format.\n\n"
    "The BremsstrahlungAngularSpectrumBlock class contains 1 array with\n"
    "the ratio values of photon energy over electron energy for the\n"
    "bremsstrahlung angular spectrum calculation (NEL == 3).\n\n"
    "The size NRKA is stored in NXS(10)."
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

    "NRKA",
    &Block::NRKA,
    "The number of bremstrahlung angular spectrum points"
  )
  .def_property_readonly(

    "number_photon_energy_ratios",
    &Block::numberPhotonEnergyRatios,
    "The number of bremstrahlung angular spectrum points"
  )
  .def_property_readonly(
  
    "photon_energy_ratios",
    [] ( const Block& self ) -> DoubleRange
       { return self.photonEnergyRatios(); },
    "The energy points for bremstrahlung angular spectrum interpolation"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
