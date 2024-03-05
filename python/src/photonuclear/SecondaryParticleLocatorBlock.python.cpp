// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/photonuclear/SecondaryParticleLocatorBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace photonuclear {

void wrapSecondaryParticleLocatorBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::photonuclear::SecondaryParticleLocatorBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleLocatorBlock",
    "The photonuclear IXSU block with the secondary particle information and locators\n\n"
    "The SecondaryParticleLocatorBlock class contains a particle type, a number\n"
    "of reactions and 10 locators for each secondary particle type.\n\n"
    "The number of available available particle types is stored in NXS(5)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int >,
                  std::vector< unsigned int >,
                  std::vector< std::array< unsigned int, 10 > > >(),
    python::arg( "types" ), python::arg( "numbers" ), python::arg( "locators" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    types       the particle types\n"
    "    numbers     the number of reactions for each particle type\n"
    "    locators    the locators for each secondary particle type"
  )
  .def_property_readonly(

    "NTYPE",
    &Block::NTYPE,
    "The number of secondary particle types (excluding the projectile)"
  )
  .def_property_readonly(

    "number_additional_secondary_particle_types",
    &Block::numberAdditionalSecondaryParticleTypes,
    "The number of secondary particle types (excluding the projectile)"
  )
  .def(

    "IP",
    &Block::IP,
    python::arg( "index" ),
    "The particle type for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "particle_type",
    &Block::particleType,
    python::arg( "index" ),
    "The particle type for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "NP",
    &Block::NP,
    python::arg( "index" ),
    "The number of reactions for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "number_secondary_particle_production_reactions",
    &Block::numberSecondaryParticleProductionReactions,
    python::arg( "index" ),
    "The number of reactions for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "PXS",
    &Block::PXS,
    python::arg( "index" ),
    "The locator to the PXS block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "PHN",
    &Block::PHN,
    python::arg( "index" ),
    "The locator to the PHN block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "MTRH",
    &Block::MTRH,
    python::arg( "index" ),
    "The locator to the MTRH block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "TYRH",
    &Block::TYRH,
    python::arg( "index" ),
    "The locator to the TYRH block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "LSIGH",
    &Block::LSIGH,
    python::arg( "index" ),
    "The locator to the LSIGH block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "SIGH",
    &Block::SIGH,
    python::arg( "index" ),
    "The locator to the SIGH block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "LANDH",
    &Block::LANDH,
    python::arg( "index" ),
    "The locator to the LANDH block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "ANDH",
    &Block::ANDH,
    python::arg( "index" ),
    "The locator to the ANDH block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "LDLWH",
    &Block::LDLWH,
    python::arg( "index" ),
    "The locator to the LDLWH block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "DLWH",
    &Block::DLWH,
    python::arg( "index" ),
    "The locator to the DLWH block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  )
  .def(

    "has_IP",
    &Block::hasIP,
    python::arg( "type" ),
    "Return whether or not the particle type is present\n\n"
    "    self    the block\n"
    "    type    the particle type"
  )
  .def(

    "has_particle_type",
    &Block::hasParticleType,
    python::arg( "type" ),
    "Return whether or not the particle type is present\n\n"
    "    self    the block\n"
    "    type    the particle type"
  )
  .def(

    "index",
    &Block::index,
    python::arg( "type" ),
    "Return the index (one-based) of the particle type\n\n"
    "    self    the block\n"
    "    type    the particle type"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // photonuclear namespace
