// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/AngularDistributionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapAngularDistributionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::AngularDistributionBlock;
  using DistributionData = Block::DistributionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "AngularDistributionBlock",
    "The AngularDistributionBlock class contains angular distribution data,\n"
    "one for each the first NXS(5) reaction numbers on the MTR block and\n"
    "elastic as well (referenced using the reaction index 0). Elastic is always\n"
    "the first reaction (hence the index 0 for this reaction) while the order\n"
    "of the other distribution data sets is the same as the order of the reaction\n"
    "numbers in the MTR block."
  );

  // wrap the block
  block
  .def(

    python::init< DistributionData, std::vector< DistributionData > >(),
    python::arg( "elastic" ), python::arg( "distributions" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    elastic          the angular distribution data for elastic\n"
    "    distributions    the angular distribution data"
  )
  .def_property_readonly(

    "NR",
    &Block::NR,
    "The number of reactions excluding elastic that produce the projectile"
  )
  .def_property_readonly(

    "number_projectile_production_reactions",
    &Block::numberProjectileProductionReactions,
    "The number of reactions excluding elastic that produce the projectile"
  )
  .def_property_readonly(

    "total_number_projectile_production_reactions",
    &Block::totalNumberProjectileProductionReactions,
    "The number of reactions excluding elastic that produce the projectile"
  )
  .def(

    "LAND",
    &Block::LAND,
    python::arg( "index" ),
    "Return the relative angular distribution locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based, zero for elastic)"
  )
  .def(

    "angular_distribution_locator",
    &Block::angularDistributionLocator,
    python::arg( "index" ),
    "Return the relative angular distribution locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based, zero for elastic)"
  )
  .def(

    "is_fully_isotropic",
    &Block::isFullyIsotropic,
    python::arg( "index" ),
    "Return whether or not the distribution data is fully isotropic for\n"
    "a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based, zero for elastic)"
  )
  .def(

    "is_given",
    &Block::isGiven,
    python::arg( "index" ),
    "Return whether or not the distribution data is fully isotropic for\n"
    "is given in the AND block\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based, zero for elastic)"
  )
  .def_property_readonly(

    "data",
    &Block::data,
    "All angular distribution data"
  )
  .def(

    "angular_distribution_data",
    &Block::angularDistributionData,
    python::arg( "index" ),
    "Return the angular distribution data for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based, zero for elastic)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
