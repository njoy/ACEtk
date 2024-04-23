// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/EnergyDistributionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapEnergyDistributionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::electron::EnergyDistributionBlock;
  using TabulatedEnergyDistribution = njoy::ACEtk::electron::TabulatedEnergyDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EnergyDistributionBlock",
    "The energy distribution block for photons from Bremsstrahlung or knock-on\n"
    "electrons for a specific subshell\n\n"
    "The EnergyDistributionBlock class contains a list of electron energies\n"
    "for which energy distribution data is given (for either photons in the\n"
    "BREMI/BREME block or electrons in the EION blocks)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< TabulatedEnergyDistribution > >(),
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

} // electron namespace
