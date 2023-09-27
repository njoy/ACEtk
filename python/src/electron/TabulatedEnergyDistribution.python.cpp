// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ElectronTabulatedEnergyDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapElectronTabulatedEnergyDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ElectronTabulatedEnergyDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ElectronTabulatedEnergyDistribution",
    "Tabulated photon energy distribution from Bremsstrahlung for a single incident energy\n\n"
    "The ElectronTabulatedEnergyDistribution class contains the cumulative\n"
    "density function (CDF) as a function of photon energy for the given incident\n"
    "energy. It is used in the BREME block."
  );

  // wrap the block
  block
  .def(

    python::init< double, std::vector< double >, std::vector< double > >(),
    python::arg( "energy" ),  python::arg( "outgoing" ), python::arg( "cdf" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    energy      the associated incident energy value\n"
    "    outgoing    the outgoing energy values\n"
    "    cdf         the cdf values"
  )
  .def_property_readonly(

    "energy",
    &Block::energy,
    "The associated incident energy value"
  )
  .def_property_readonly(

    "number_outgoing_energies",
    &Block::numberOutgoingEnergies,
    "The number of outgoing energy values"
  )
  .def_property_readonly(

    "outgoing_energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.outgoingEnergies(); },
    "The cosine values"
  )
  .def_property_readonly(

    "cdf",
    [] ( const Block& self ) -> DoubleRange
       { return self.cdf(); },
    "The cdf values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
