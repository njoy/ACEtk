// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ElectronBremsstrahlungEnergyDistributionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapElectronBremsstrahlungEnergyDistributionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ElectronBremsstrahlungEnergyDistributionBlock;
  using ElectronTabulatedEnergyDistribution = njoy::ACEtk::block::ElectronTabulatedEnergyDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ElectronBremsstrahlungEnergyDistributionBlock",
    "The photoatomic and electron BREMI and BREME block with the photon energy\n"
    "distribution data from Bremsstrahlung\n\n"
    "The ElectronElasticAngularDistributionBlock class contains a list of\n"
    "electron energies for which energy distribution data is given."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< ElectronTabulatedEnergyDistribution > >(),
    python::arg( "distributions" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    distributions    the energy distribution data"
  )
  .def_property_readonly(

    "NB",
    &Block::NB,
    "The number of available energies"
  )
  .def_property_readonly(

    "number_energy_points",
    &Block::numberEnergyPoints,
    "The number of available energies"
  )
  .def(

    "LLOC",
    &Block::LLOC,
    python::arg( "index" ),
    "Return the relative distribution locator for an energy index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "distribution_locator",
    &Block::distributionLocator,
    python::arg( "index" ),
    "Return the relative distribution locator for an energy index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "distributions",
    &Block::distributions,
    "The angular distribution data"
  )
  .def(

    "distribution",
    &Block::distribution,
    python::arg( "index" ),
    "Return the angular distribution for an energy index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
