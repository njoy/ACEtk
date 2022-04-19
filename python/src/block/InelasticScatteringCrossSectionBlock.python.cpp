// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/InelasticScatteringCrossSectionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapInelasticScatteringCrossSectionBlock( python::module& module,
                                               python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::InelasticScatteringCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "InelasticScatteringCrossSectionBlock",
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

    "NIN",
    &Block::NIN,
    "The number of inelastic energies"
  )
  .def_property_readonly(

    "number_inelastic_energies",
    &Block::numberInelasticEnergies,
    "The number of inelastic energies"
  )
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> LongRange
       { return self.energies(); },
    "The inelastic energies"
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Block& self ) -> LongRange
       { return self.crossSections(); },
    "The inelastic cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
