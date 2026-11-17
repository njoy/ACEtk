// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/OscillatorBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapOscillatorBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::OscillatorBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "OscillatorBlock",
    "The electron CRB block with the oscillator descriptions\n\n"
    "This block is part of the el03 format.\n\n"
    "The OscillatorBlock class contains 2 arrays of the\n"
    "same length:\n"
    "  - The level occupation numbers\n"
    "  - The level binding energies\n\n"
    "The size NOSC of each (the total number of oscillator points) is stored\n"
    "in NXS(11)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "occupation_numbers" ), python::arg( "binding_energies" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    occupation_numbers    The occupation numbers of each subshell\n"
    "    binding_energies      The binding energies of each subshell"
  )
  .def_property_readonly(

    "NOSC",
    &Block::NOSC,
    "The number of oscillators"
  )
  .def_property_readonly(

    "number_oscillators",
    &Block::numberOscillators,
    "The number of oscillators"
  )
  .def_property_readonly(
  
    "occupation_numbers",
    [] ( const Block& self ) -> DoubleRange
       { return self.occupationNumbers(); },
    "The occupation numbers of each level\n\n"
    "n < 0 at the last (highest) level signifies a conductor"
  )
  .def_property_readonly(
  
    "binding_energies",
    [] (const Block& self ) -> DoubleRange
       { return self.bindingEnergies(); },
    "The binding energies of each level"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
