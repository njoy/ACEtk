// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/SecondaryParticleEnergyDistributionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapSecondaryParticleEnergyDistributionBlock( python::module& module,
                                                   python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::SecondaryParticleEnergyDistributionBlock;
  using EnergyDistributionData = njoy::ACEtk::block::EnergyDistributionData;
  using ReferenceFrame = njoy::ACEtk::ReferenceFrame;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleEnergyDistributionBlock",
    "The continuous energy LDLWP, DLWP and LDLWH, DLWH blocks with the\n"
    "energy distribution data for secondary particles that are not the\n"
    "incident particle type\n\n"
    "The SecondaryParticleAngularDistributionBlock class contains energy\n"
    "distribution data, one for each the NXS(6) reaction numbers on the MTRP\n"
    "block (for the LANDP, ANDP blocks) and each of the NTRO(ITYPE) reactions on\n"
    "the MTRH(ITYPE) block. The order of the distribution data sets is the same\n"
    "as the order of the reaction numbers in the corresponding MTR block."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< EnergyDistributionData > >(),
    python::arg( "distributions" ),
    "Initialise the DNED block\n\n"
    "Arguments:\n"
    "    self              the block\n"
    "    distributions     the energy distribution data"
  )
  .def(

    python::init< std::vector< EnergyDistributionData >,
                  std::vector< ReferenceFrame > >(),
    python::arg( "distributions" ), python::arg( "frames" ),
    "Initialise the DLWH block\n\n"
    "Arguments:\n"
    "    self              the block\n"
    "    distributions     the energy distribution data\n"
    "    frames            the reference frames"
  )
  .def_property_readonly(

    "NR",
    &Block::NR,
    "The number of reactions with energy distribution data"
  )
  .def_property_readonly(

    "number_reactions",
    &Block::numberReactions,
    "The number of reactions with energy distribution data"
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
  )
  .def_property_readonly(

    "reference_frames",
    &Block::referenceFrames,
    "The reference frames"
  )
  .def(

    "reference_frame",
    &Block::referenceFrame,
    python::arg( "index" ),
    "Return the reference frame for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
