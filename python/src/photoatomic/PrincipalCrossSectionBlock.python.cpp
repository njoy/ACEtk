// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/photoatomic/PrincipalCrossSectionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace photoatomic {

void wrapPrincipalCrossSectionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::photoatomic::PrincipalCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PrincipalCrossSectionBlock",
    "The photoatomic ESZG block with the principal cross sections\n\n"
    "The PrincipalCrossSectionBlock class contains 5 arrays of the same length\n"
    "(all values are stored as the natural logarithm):\n"
    "  - the energy points\n"
    "  - the incoherent cross section\n"
    "  - the coherent cross section\n"
    "  - the photoelectric cross section\n"
    "  - the pair production cross section\n\n"
    "The size of each (the total number of energy points) is stored in NXS(3)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "energies" ), python::arg( "incoherent" ),
    python::arg( "coherent" ), python::arg( "photoelectric" ),
    python::arg( "pairproduction" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self              the block\n"
    "    energies          the energy values\n"
    "    incoherent        the incoherent cross section values\n"
    "    coherent          the coherent cross section values\n"
    "    photoelectric     the photoelectric cross section values\n"
    "    pairproduction    the pair production cross section values"
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

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "incoherent",
    [] ( const Block& self ) -> DoubleRange
       { return self.incoherent(); },
    "The incoherent cross section values"
  )
  .def_property_readonly(

    "coherent",
    [] ( const Block& self ) -> DoubleRange
       { return self.coherent(); },
    "The coherent cross section values"
  )
  .def_property_readonly(

    "photoelectric",
    [] ( const Block& self ) -> DoubleRange
       { return self.photoelectric(); },
    "The photoelectric cross section values"
  )
  .def_property_readonly(

    "pairproduction",
    [] ( const Block& self ) -> DoubleRange
       { return self.pairproduction(); },
    "The pair production cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // photoatomic namespace
