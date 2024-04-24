// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/FissionMultiplicityBlock.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapFissionMultiplicityBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::FissionMultiplicityBlock;
  using FissionMultiplicityData = njoy::ACEtk::continuous::FissionMultiplicityBlock::FissionMultiplicityData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "FissionMultiplicityBlock",
    "The continuous energy NU block with the fission multiplicity data."
  );

  // wrap the block
  block
  .def(

    python::init< FissionMultiplicityData >(),
    python::arg( "prompt" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self      the block\n"
    "    prompt    the prompt fission multiplicity data"
  )
  .def(

    python::init< FissionMultiplicityData, FissionMultiplicityData >(),
    python::arg( "prompt" ), python::arg( "total" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self      the block\n"
    "    prompt    the prompt fission multiplicity data\n"
    "    total     the total fission multiplicity data"
  )
  .def_property_readonly(

    "has_prompt_and_total_fission_multiplicity",
    &Block::hasPromptAndTotalFissionMultiplicity,
    "Flag to see whether or not prompt and total fission multiplicity are present"
  )
  .def_property_readonly(

    "multiplicity",
    &Block::multiplicity,
    "The prompt fission multiplicity\n"
    "This returns the prompt fission multiplicity when both prompt and total\n"
    "are given or just the available multiplicity data if only one of these is\n"
    "given (the ACE format does not indicate which is present)."
  )
  .def_property_readonly(

    "total_fission_multiplicity",
    &Block::totalFissionMultiplicity,
    "The total fission multiplicity\n"
    "This returns the total fission multiplicity when both prompt and total\n"
    "are given or just the available multiplicity data if only one of these is\n"
    "given (the ACE format does not indicate which is present)."
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
