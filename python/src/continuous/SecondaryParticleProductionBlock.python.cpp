// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/SecondaryParticleProductionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapSecondaryParticleProductionBlock( python::module& module,
                                           python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::SecondaryParticleProductionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleProductionBlock",
    "Total production cross section and heating numbers for a secondary particle"
  );

  // wrap the block
  block
  .def(

    python::init< std::size_t, std::vector< double >, std::vector< double > >(),
    python::arg( "index" ), python::arg( "production" ), python::arg( "heating" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self          the block\n"
    "    index         the energy index\n"
    "    production    the total production cross section values"
    "    heating       the heating numbers"
  )
  .def_property_readonly(

    "energy_index",
    &Block::energyIndex,
    "The energy index"
  )
  .def_property_readonly(

    "number_values",
    &Block::numberValues,
    "The number of cross section values"
  )
  .def_property_readonly(

    "total_production",
    [] ( const Block& self ) -> DoubleRange
       { return self.totalProduction(); },
    "The total poduction cross section values"
  )
  .def_property_readonly(

    "heating",
    [] ( const Block& self ) -> DoubleRange
       { return self.heating(); },
    "The heating numbers"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
