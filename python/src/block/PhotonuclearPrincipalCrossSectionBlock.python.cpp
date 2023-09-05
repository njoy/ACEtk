// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/PhotonuclearPrincipalCrossSectionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotonuclearPrincipalCrossSectionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotonuclearPrincipalCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotonuclearPrincipalCrossSectionBlock",
    "The photoatomic ESZG block with the principal cross sections\n\n"
    "The PhotonuclearPrincipalCrossSectionBlock class contains 3 or 4 arrays of the\n"
    "same length:\n"
    "  - the energy points\n"
    "  - the total cross section\n"
    "  - the elastic scattering cross section (optional)\n"
    "  - the heating numbers\n\n"
    "The size of each (the total number of energy points) is stored in NXS(3)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "energies" ), python::arg( "total" ),
    python::arg( "heating" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    energies    the energy values\n"
    "    total       the total cross section values\n"
    "    heating     the average heating cross section values"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ), python::arg( "total" ),
    python::arg( "elastic" ), python::arg( "heating" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    energies    the energy values\n"
    "    total       the total cross section values\n"
    "    elastic     the elastic cross section values\n"
    "    heating     the average heating cross section values"
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

    "total",
    [] ( const Block& self ) -> DoubleRange
       { return self.total(); },
    "The total cross section values"
  )
  .def_property_readonly(

    "elastic",
    [] ( const Block& self ) -> DoubleRange
       { return self.elastic(); },
    "The elastic cross section values (this can be empty)"
  )
  .def_property_readonly(

    "heating",
    [] ( const Block& self ) -> DoubleRange
       { return self.heating(); },
    "The average heating cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
