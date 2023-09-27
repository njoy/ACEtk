// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/PrincipalCrossSectionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapPrincipalCrossSectionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::PrincipalCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PrincipalCrossSectionBlock",
    "The electron ESZE block with the electron cross section data\n\n"
    "This block is part of the eprdata formats.\n\n"
    "The PrincipalCrossSectionBlock class contains 5 + NSSH arrays of the same length:\n"
    "  - the energy points\n"
    "  - the total cross section (sum of the following three arrays)\n"
    "  - the large angle elastic scattering cross section\n"
    "  - the Bremsstrahlung cross section\n"
    "  - the excitation cross section\n"
    "  - the total electroionisation cross section (sum of the following NSSH arrays)\n"
    "  - the electroionisation cross section for each subshell (NSSH arrays)\n\n"
    "The size NE of each (the total number of electron energy points) is stored in\n"
    "NXS(8). The number of subshells NSSH is stored in NXS(7)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double >,
                  std::vector< std::vector< double > > >(),
    python::arg( "energies" ), python::arg( "elastic" ),
    python::arg( "bremsstrahlung" ), python::arg( "excitation" ),
    python::arg( "electroionisation" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self                 the block\n"
    "    energies             the energy values\n"
    "    elastic              the elastic cross section values\n"
    "    bremsstrahlung       the Bremsstrahlung cross section values\n"
    "    excitation           the excitation cross section values\n"
    "    electroionisation    the electroionisation cross section values"
  )
  .def_property_readonly(

    "NE",
    &Block::NE,
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
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "total",
    [] ( const Block& self ) -> DoubleRange
       { return self.total(); },
    "The total cross section values"
  )
  .def_property_readonly(

    "elastic",
    [] ( const Block& self ) -> DoubleRange
       { return self.elastic(); },
    "The large angle elastic cross section values"
  )
  .def_property_readonly(

    "bremsstrahlung",
    [] ( const Block& self ) -> DoubleRange
       { return self.bremsstrahlung(); },
    "The Bremsstrahlung cross section values"
  )
  .def_property_readonly(

    "excitation",
    [] ( const Block& self ) -> DoubleRange
       { return self.excitation(); },
    "The excitation cross section values"
  )
  .def_property_readonly(

    "total_electroionisation",
    [] ( const Block& self ) -> DoubleRange
       { return self.totalElectroionisation(); },
    "The total electroionisation cross section values"
  )
  .def(

    "electroionisation",
    [] ( const Block& self, std::size_t index ) -> DoubleRange
       { return self.electroionisation( index ); },
    python::arg( "index" ),
    "The electroionisation cross section values for a specific shell\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the electron shell index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // electron namespace
