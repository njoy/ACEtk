// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/SecondaryParticleAngularDistributionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapSecondaryParticleAngularDistributionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::SecondaryParticleAngularDistributionBlock;
  using DistributionData = Block::DistributionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleAngularDistributionBlock",
    "The continuous energy LANDP, ANDP and LANDH, ANDH blocks with the\n"
    "angular distribution data for secondary particles that are not the\n"
    "incident particle type\n\n"
    "The SecondaryParticleAngularDistributionBlock class contains angular\n"
    "distribution data, one for each the NXS(6) reaction numbers on the MTRP\n"
    "block (for the LANDP, ANDP blocks) and each of the NTRO(ITYPE) reactions on\n"
    "the MTRH(ITYPE) block. The order of the distribution data sets is the same\n"
    "as the order of the reaction numbers in the corresponding MTR block."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< DistributionData > >(),
    python::arg( "distributions" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    distributions    the angular distribution data"
  )
  .def_property_readonly(

    "NR",
    &Block::NR,
    "The number of reactions with angular distribution data"
  )
  .def_property_readonly(

    "number_reactions",
    &Block::numberReactions,
    "The number of reactions with angular distribution data"
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
    "Return whether or not the distribution data is given in the AND block\n\n"
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

} // block namespace
