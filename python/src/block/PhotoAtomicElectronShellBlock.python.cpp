// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/PhotoAtomicElectronShellBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotoAtomicElectronShellBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotoAtomicElectronShellBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotoAtomicElectronShellBlock",
    "The photoatomic LNEPS, LBEPS and LPIPS block with the electron shell data\n\n"
    "The PhotoAtomicPrincipalCrossSectionBlock class contains 3 arrays of the\n"
    "same length:\n"
    "  - the number of electrons for each shell\n"
    "  - the binding energy for each shell\n"
    "  - the interaction probability for each shell\n"
    "The size of each (the total number of electron shells) is stored in NXS(5)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "electrons" ), python::arg( "energies" ),
    python::arg( "probabilities" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    electrons        the number of electrons for each shell\n"
    "    energies         the binding energy for each shell\n"
    "    probabilities    the interaction probability for each shell"
  )
  .def_property_readonly(

    "NSH",
    &Block::NSH,
    "The number of electron shells"
  )
  .def_property_readonly(

    "number_electron_shells",
    &Block::numberElectronShells,
    "The number of electron shells"
  )
  .def_property_readonly(

    "LNEPS",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.LNEPS(); },
    "The number of electrons for each shell"
  )
  .def_property_readonly(

    "number_electrons",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.numberElectrons(); },
    "The number of electrons for each shell"
  )
  .def_property_readonly(

    "LBEPS",
    [] ( const Block& self ) -> DoubleRange
       { return self.LBEPS(); },
       "The binding energies for each shell"
  )
  .def_property_readonly(

    "binding_energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.bindingEnergies(); },
    "The binding energies for each shell"
  )
  .def_property_readonly(

    "LPIPS",
    [] ( const Block& self ) -> DoubleRange
       { return self.LPIPS(); },
    "The interaction probability for each shell"
  )
  .def_property_readonly(

    "interaction_probabilities",
    [] ( const Block& self ) -> DoubleRange
       { return self.interactionProbabilities(); },
    "The interaction probability for each shell"
  )
  .def(

    "number_electrons_per_shell",
    &Block::numberElectronsPerShell,
    python::arg( "index" ),
    "The number of electrons on a specific shell\n\n"
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

    "interaction_probability",
    &Block::interactionProbability,
    python::arg( "index" ),
    "The interaction probability for a specific shell\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the electron shell index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
