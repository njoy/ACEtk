// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/SecondaryParticleProductionCrossSectionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapSecondaryParticleProductionCrossSectionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::SecondaryParticleProductionCrossSectionBlock;
  using TabulatedSecondaryParticleMultiplicity = njoy::ACEtk::block::TabulatedSecondaryParticleMultiplicity;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleProductionCrossSectionBlock",
    "The continuous energy LSIGH and SIGH block with the secondary particle\n"
    "production cross section data (multiplicity data only)\n\n"
    "The SecondaryParticleProductionCrossSectionBlock class contains NTRO.NP sets\n"
    "of secondary particle production data, one for each reaction number on the\n"
    "MTRH block. The order of these cross section data sets is the same as the\n"
    "order of the reaction numbers in the MTRH block."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< TabulatedSecondaryParticleMultiplicity > >(),
    python::arg( "xs" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self    the block\n"
    "    xs      the cross section data"
  )
  .def_property_readonly(

    "NP",
    &Block::NP,
    "The number of secondary particle production reactions"
  )
  .def_property_readonly(

    "number_secondary_particle_production_reactions",
    &Block::numberSecondaryParticleProductionReactions,
    "The number of secondary particle production reactions"
  )
  .def(

    "LSIG",
    &Block::LSIG,
    python::arg( "index" ),
    "Return the relative cross section locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "cross_section_locator",
    &Block::crossSectionLocator,
    python::arg( "index" ),
    "Return the relative cross section locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "data",
    &Block::data,
    "The cross section data"
  )
  .def(

    "cross_section_data",
    &Block::crossSectionData,
    python::arg( "index" ),
    "Return the cross section data for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
