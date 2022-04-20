// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ThermalScatteringCrossSectionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapThermalScatteringCrossSectionBlock( python::module& module,
                                               python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ThermalScatteringCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ThermalScatteringCrossSectionBlock",
    "The inelastic thermal scattering cross section block"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "energies" ), python::arg( "xs" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    energies    the inelastic energies\n"
    "    xs          the inelastic cross section values"
  )
  .def_property_readonly(

    "NE",
    &Block::NE,
    "The number of energies"
  )
  .def_property_readonly(

    "number_energies",
    &Block::numberEnergies,
    "The number of energies"
  )
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The inelastic energies"
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Block& self ) -> DoubleRange
       { return self.crossSections(); },
    "The inelastic cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
