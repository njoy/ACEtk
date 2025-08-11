// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/BremsstrahlungProductionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapBremsstrahlungProductionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::BremsstrahlungProductionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "BremsstrahlungProductionBlock",
    "The electron XSB block with the bremsstrahlung photon production data\n\n"
    "This block is part of el03 format.\n\n"
    "The BremsstrahlungProductionBlock class contains a variable number of\n"
    "arrays of differing lengths:\n"
    "  - The electron energy points\n"
    "  - The photon energy ratio points\n"
    "  - The cross section values\n\n"
    "The size NEB of the electron energy values array (the total number of\n"
    "electron energy points) is stored in NXS(5). The size NPB of the photon\n"
    "energy ratio values array (the total number of photon energy points) is\n"
    "stored in NXS(6). The size of the bremsstrahlung production cross\n"
    "section array (the number of values for interpolation) is NEB*NPB.\n\n"
    "The cross section values are stored internally in column-major order."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::vector< double > > >(),
    python::arg( "electron_energies" ), python::arg( "photon_ratios" ),
    python::arg( "cross_sections" ),
    "Initialize the block\n\n"
    "Arguments:\n"
    "    electron_energies    the electron energy points\n"
    "    photon_ratios        the photon energy ratio points\n"
    "    cross_sections       the bremsstrahlung cross section values"
  )
  .def_property_readonly(
  
    "NEB",
    &Block::NEB,
    "The number of electron energy points"
  )
  .def_property_readonly(
  
    "number_electron_energies",
    &Block::numberElectronEnergies,
    "The number of electron energy points"
  )
  .def_property_readonly(
  
    "NPB",
    &Block::NPB,
    "The number of photon energy ratio points"
  )
  .def_property_readonly(
  
    "number_photon_ratios",
    &Block::numberPhotonRatios,
    "The number of photon energy ratio points"
  )
  .def_property_readonly(
  
    "number_cross_sections",
    &Block::numberCrossSections,
    "The number of cross section values"
  )
  .def(
  
    "electron_energy",
    &Block::electronEnergy,
    "A single electron energy point\n\n"
    "Arguments:\n"
    "    index   the electron energy index (one-based)"
  )
  .def_property_readonly(
  
    "electron_energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.electronEnergies(); },
    "The electron energy points"
  )
  .def(
  
    "photon_ratio",
    &Block::photonRatio,
    "A single photon energy ratio point\n\n"
    "Arguments:\n"
    "    index   the photon energy ratio index (one-based)"
  )
  .def_property_readonly(
  
    "photon_ratios",
    [] ( const Block& self ) -> DoubleRange
       { return self.photonRatios(); },
    "The photon energy ratio points"
  )
  .def(
  
    "cross_section",
    &Block::crossSection,
    "A single bremsstrahlung cross section value\n\n"
    "Arguments:\n"
    "    ee_index    the electron energy index (one-based)\n"
    "    pr_index    the photon energy ratio index (one-based)"
  )
  .def(
  
    "cross_sections",
    [] ( const Block& self, std::size_t index ) -> DoubleRange
       { return self.crossSections( index ); },
    "The cross section values for a given electron energy index\n\n"
    "Arguments:\n"
    "    index   the electron energy index (one-based)"
  )
  .def_property_readonly(
  
    "cross_section_data",
    [] ( const Block& self ) -> DoubleRange
       { return self.crossSectionData(); },
    "The bremsstrahlung cross section data array"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
