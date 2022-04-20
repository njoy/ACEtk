// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ThermalScatteringEquiprobableAngularBins.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapThermalScatteringEquiprobableAngularBins( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ThermalScatteringEquiprobableAngularBins;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ThermalScatteringEquiprobableAngularBins",
    "Equiprobable angular bin data for a single outgoing energy value\n\n"
    "The ThermalScatteringEquiprobableAngularBins class contains the outgoing\n"
    "energy value and the cosine values that make up the equiprobable bins\n"
    "(contrary to the AND block, the number of bins is not fixed and can vary).\n"
    "It is used in the ITXE block (for inelastic thermal scattering data)."
  );

  // wrap the block
  block
  .def(

    python::init< double, std::vector< double > >(),
    python::arg( "energy" ), python::arg( "cosines" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    energy      the outgoing energy value\n"
    "    cosines     the cosine values"
  )
  .def_property_readonly(

    "energy",
    &Block::energy,
    "The outgoing energy value"
  )
  .def_property_readonly(

    "number_bins",
    [] ( const Block& self ) { return self.numberBins(); },
    "The number of equiprobable angular bins"
  )
  .def_property_readonly(

    "cosines",
    [] ( const Block& self ) -> DoubleRange
       { return self.cosines(); },
    "The cosine values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
