// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/SubshellTransitionData.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapSubshellTransitionData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::SubshellTransitionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SubshellTransitionData",
    "The electron transition data for a given subshell\n\n"
    "This block is part of the eprdata formats.\n\n"
    "The SubshellTransitionData class contains the transition data to fill vacancies\n"
    "in the given subshell. Each transition has the following information associated to it:\n"
    "  - the primary subshell designator (the designator of the subshell from\n"
    "    where the electron is \"moving\" from)\n"
    "  - the secondary subshell designator (the designator of the subshell from\n"
    "    which the emitted electron is ejected or 0 for a radiative transition\n"
    "    that only emits a photon)\n"
    "  - the energy of the emitted photon or electron\n"
    "  - the cumulative probability of the transition\n\n"
    "The size NT of each (the total number of transitions) is stored in the SUBSH\n"
    "block. This data block may be empty (NT = 0)."
  );

  // wrap the block
  block
  .def(

    python::init<>(),
    "Initialise an empty block"
  )
  .def(

    python::init< std::vector< unsigned int >, std::vector< unsigned int >,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "primary" ), python::arg( "secondary" ),
    python::arg( "energies" ), python::arg( "probabilities" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    primary          the primary subshell designators\n"
    "    secondary        the secondary subshell designators\n"
    "    energies         the energy values of the secondary photon or electron\n"
    "    probabilities    the cumulative probabilities of the transitions"
  )
  .def_property_readonly(

    "NT",
    &Block::NT,
    "The number of transitions"
  )
  .def_property_readonly(

    "number_transitions",
    &Block::numberTransitions,
    "The number of transitions"
  )
  .def(

    "transition",
    [] ( const Block& self, std::size_t index ) -> DoubleRange
       { return self.transition( index ); },
    "The transition data for a given transition\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the transition index (one-based)"
  )
  .def(

    "primary_designator",
    python::overload_cast< std::size_t >( &Block::primaryDesignator, python::const_ ),
    python::arg( "index" ),
    "The primary designator for a given transition\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the transition index (one-based)"
  )
  .def(

    "secondary_designator",
    python::overload_cast< std::size_t >( &Block::secondaryDesignator, python::const_ ),
    python::arg( "index" ),
    "The secondary designator for a given transition\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the transition index (one-based)"
  )
  .def(

    "energy",
    python::overload_cast< std::size_t >( &Block::energy, python::const_ ),
    python::arg( "index" ),
    "The energy of the secondary photon or electron for a given transition\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the transition index (one-based)"
  )
  .def(

    "probability",
    python::overload_cast< std::size_t >( &Block::probability, python::const_ ),
    python::arg( "index" ),
    "The cumulative probability for a given transition\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the transition index (one-based)"
  )
  .def(

    "is_radiative_transition",
    python::overload_cast< std::size_t >( &Block::isRadiativeTransition, python::const_ ),
    python::arg( "index" ),
    "Return whether or not the transition is a radiative transitions\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the transition index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
