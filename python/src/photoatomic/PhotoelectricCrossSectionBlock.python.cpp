// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/photoatomic/PhotoelectricCrossSectionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace photoatomic {

void wrapPhotoelectricCrossSectionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::photoatomic::PhotoelectricCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotoelectricCrossSectionBlock",
    "The photoatomic SPHEL block with the photoelectric cross section for each subshell\n\n"
    "This block is part of the eprdata formats.\n\n"
    "The PhotoelectricCrossSectionBlock class contains NSSH arrays of the same\n"
    "length, each one being the photoelectric cross section of a subshell.\n\n"
    "The size of each (the total number of energy points NES) is stored in NXS(3)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< std::vector< double > > >(),
    python::arg( "photoelectric" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self              the block\n"
    "    photoelectric    the photoelectric cross section values for each shell"
  )
  .def_property_readonly(

    "NES",
    &Block::NES,
    "The number of energy points"
  )
  .def_property_readonly(

    "number_energy_points",
    &Block::numberEnergyPoints,
    "The number of energy points"
  )
  .def_property_readonly(

    "NSSH",
    &Block::NSSH,
    "The number of electron subshells"
  )
  .def_property_readonly(

    "number_electron_subshells",
    &Block::numberElectronSubshells,
    "The number of electron subshells"
  )
  .def(

    "photoelectric",
    [] ( const Block& self, std::size_t index ) -> DoubleRange
       { return self.photoelectric( index ); },
    python::arg( "index" ),
    "The photoelectric cross section values for a specific shell\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the electron shell index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // photoatomic namespace
