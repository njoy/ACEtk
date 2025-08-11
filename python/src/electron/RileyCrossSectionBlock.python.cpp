// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/RileyCrossSectionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapRileyCrossSectionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::RileyCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "RileyCrossSectionBlock",
    "The electron RLY block with the Riley cross section data\n\n"
    "This block is part of el and el03 formats.\n\n"
    "The RileyCrossSectionBlock class contains 9 arrays of the same length.\n"
    "Each array contains an energy value from 1 to 256 keV followed by the\n"
    "set of Riley scattering cross section parameters at that energy.\n\n"
    "The size of each Riley set array is 14 (1 energy + 13 parameters).\n"
    "This size value is hard-coded and is not stored in the NXS array."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "rileySet256keV" ), python::arg( "rileySet128keV" ),
    python::arg( "rileySet64keV" ), python::arg( "rileySet32keV" ),
    python::arg( "rileySet16keV" ), python::arg( "rileySet8keV" ),
    python::arg( "rileySet4keV" ), python::arg( "rileySet2keV" ),
    python::arg( "rileySet1keV" ),
    "Initialize the block\n\n"
    "Arguments:\n"
    "    rileySet256keV    the Riley cross section parameters at 256 keV\n"
    "    rileySet128keV    the Riley cross section parameters at 128 keV\n"
    "    rileySet64keV     the Riley cross section parameters at 64 keV\n"
    "    rileySet32keV     the Riley cross section parameters at 32 keV\n"
    "    rileySet16keV     the Riley cross section parameters at 16 keV\n"
    "    rileySet8keV      the Riley cross section parameters at 8 keV\n"
    "    rileySet4keV      the Riley cross section parameters at 4 keV\n"
    "    rileySet2keV      the Riley cross section parameters at 2 keV\n"
    "    rileySet1keV      the Riley cross section parameters at 1 keV"
  )
  .def_property_readonly(
  
    "NRLY",
    &Block::NRLY,
    "The number of Riley cross section parameter sets"
  )
  .def_property_readonly(
  
    "number_energy_points",
    &Block::numberEnergyPoints,
    "The number of Riley cross section parameter sets"
  )
  .def_property_readonly(
  
    "parameter_set_length",
    &Block::parameterSetLength,
    "The length of a Riley cross section parameter set"
  )
  .def(
  
    "energy",
    &Block::energy,
    "The energy of a Riley cross section parameter set\n\n"
    "Arguments:\n"
    "    index   the index (1 to 9 inclusively, one-based)"
  )
  .def(
  
    "parameter_set",
    [] ( const Block& self, std::size_t index ) -> DoubleRange
       { return self.parameterSet( index ); },
    "The Riley cross section parameter set at the index"
    "Arguments:\n"
    "    index   the index (1 to 9 inclusively, one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
