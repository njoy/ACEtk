// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/PhotoatomicElectronSubshellBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotoatomicElectronSubshellBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotoatomicElectronSubshellBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotoatomicElectronSubshellBlock",
    "The photoatomic SUBSH block with the electron subshell data\n\n"
    "This block is part of the eprdata formats.\n\n"
    "The PhotoatomicElectronSubshellBlock class contains 5 arrays of the same length:\n"
    "  - the ENDF designator of each subshell\n"
    "  - the electron population for each subshell\n"
    "  - the binding energy for each subshell\n"
    "  - the vacancy cumulative probability for each subshell\n"
    "  - the number of possible transitions to fill a vacancy for each subshell\n"
    "The size of each (the total number of electron shells) is stored in NXS(7)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int >, std::vector< unsigned int >,
                  std::vector< double >, std::vector< double >,
                  std::vector< unsigned int > >(),
    python::arg( "designators" ), python::arg( "electrons" ),
    python::arg( "energies" ), python::arg( "probabilities" ),
    python::arg( "transitions" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    designators      the ENDF designator of each subshell\n"
    "    electrons        the electron population for each subshell\n"
    "    energies         the vacancy cumulative probability for each subshell\n"
    "    probabilities    the number of possible transitions to fill a vacancy\n"
    "                     for each subshell"
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
  .def_property_readonly(

    "ENDF",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.ENDF(); },
    "The number of electron shells"
  )
  .def_property_readonly(

    "designators",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.designators(); },
    "The number of electron shells"
  )
  .def_property_readonly(

    "EP",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.EP(); },
    "The electron population for each subshell"
  )
  .def_property_readonly(

    "populations",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.populations(); },
       "The electron population for each subshell"
  )
  .def_property_readonly(

    "BE",
    [] ( const Block& self ) -> DoubleRange
       { return self.BE(); },
       "The binding energies for each subshell"
  )
  .def_property_readonly(

    "binding_energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.bindingEnergies(); },
    "The binding energies for each subshell"
  )
  .def_property_readonly(

    "CV",
    [] ( const Block& self ) -> DoubleRange
       { return self.CV(); },
    "The vacancy probabilities for each subshell"
  )
  .def_property_readonly(

    "vacancy_probabilities",
    [] ( const Block& self ) -> DoubleRange
       { return self.vacancyProbabilities(); },
       "The vacancy probabilities for each subshell"
  )
  .def_property_readonly(

    "NT",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.NT(); },
    "The number of transitions to fill a vacancy for each subshell"
  )
  .def_property_readonly(

    "number_transitions",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.numberTransitions(); },
       "The number of transitions to fill a vacancy for each subshell"
  )
  .def(

    "designator",
    &Block::designator,
    python::arg( "index" ),
    "The ENDF designator for a specific shell\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the electron shell index (one-based)"
  )
  .def(

    "population",
    &Block::population,
    python::arg( "index" ),
    "The electron population for a specific shell\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the electron shell index (one-based)"
  )
  .def(

    "binding_energy",
    &Block::bindingEnergy,
    python::arg( "index" ),
    "The binding energy for a specific shell\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the electron shell index (one-based)"
  )
  .def(

    "vacancy_probability",
    &Block::vacancyProbability,
    python::arg( "index" ),
    "The vacancy probability for a specific shell\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the electron shell index (one-based)"
  )
  .def(

    "transitions",
    python::overload_cast< std::size_t >( &Block::numberTransitions, python::const_ ),
    python::arg( "index" ),
    "The number of transitions to fill a vacancy for a specific shell\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the electron shell index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
