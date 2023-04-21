// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/EnergyDistributionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapEnergyDistributionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::EnergyDistributionBlock;
  using EnergyDistributionData = njoy::ACEtk::block::EnergyDistributionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EnergyDistributionBlock",
    "The continuous energy LDLW and DLW block with the energy distribution data\n\n"
    "The EnergyDistributionBlock class contains energy distribution data,\n"
    "one for each the first NXS(5) reaction numbers on the MTR block. The order\n"
    "of the distribution data sets is the same as the order of the reaction\n"
    "numbers in the MTR block."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< EnergyDistributionData > >(),
    python::arg( "distributions" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    distributions    the energy distribution data"
  )
  .def_property_readonly(

    "NR",
    &Block::NR,
    "The number of reactions excluding elastic that produce the projectile"
  )
  .def_property_readonly(

    "number_reactions",
    &Block::numberReactions,
    "The number of reactions excluding elastic that produce the projectile"
  )
  .def(

    "LDLW",
    &Block::LDLW,
    python::arg( "index" ),
    "Return the relative energy distribution locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "energy_distribution_locator",
    &Block::energyDistributionLocator,
    python::arg( "index" ),
    "Return the relative energy distribution locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "data",
    &Block::data,
    "The energy distribution data"
  )
  .def(

    "energy_distribution_data",
    &Block::energyDistributionData,
    python::arg( "index" ),
    "Return the energy distribution data for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
