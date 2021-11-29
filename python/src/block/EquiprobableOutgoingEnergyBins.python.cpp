// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/EquiprobableOutgoingEnergyBins.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapEquiprobableOutgoingEnergyBins( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::EquiprobableOutgoingEnergyBins;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EquiprobableOutgoingEnergyBins",
    "Convenience interface for equiprobable cosine bin data from the DLW block"
  );

  // wrap the block
  block
  .def(

    python::init< double, std::vector< double > >(),
    python::arg( "incident" ), python::arg( "energies" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    incident    the incident energy value\n"
    "    energies    the outgoing energy values"
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

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The outgoing energy values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
