// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/EquiprobableAngularBins.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapEquiprobableAngularBins( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::EquiprobableAngularBins;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EquiprobableAngularBins",
    "Convenience interface for equiprobable cosine bin data from the AND block"
  );

  // wrap the block
  block
  .def(

    python::init< double, std::vector< double >&& >(),
    python::arg( "incident" ), python::arg( "values" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    incident    the incident energy value\n"
    "    values      the cosine values (33 values)"
  )
  .def_property_readonly(

    "incident_energy",
    &Block::incidentEnergy,
    "The incident energy"
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
