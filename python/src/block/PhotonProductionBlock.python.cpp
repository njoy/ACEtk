// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/PhotonProductionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotonProductionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotonProductionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotonProductionBlock",
    "The continuous energy GPD block with the total photon production cross section\n\n"
    "The PhotonProductionBlock class contains the total photon production cross\n"
    "section, given on the same energy grid as defined in the principal cross\n"
    "section block. For older data files, this also contains the equiprobable\n"
    "energy bins."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "production" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self          the block\n"
    "    production    the total photon production cross section values"
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

    "total_production",
    [] ( const Block& self ) -> DoubleRange
       { return self.totalProduction(); },
    "The total photon production cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
