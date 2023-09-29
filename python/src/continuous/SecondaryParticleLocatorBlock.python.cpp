// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/SecondaryParticleLocatorBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapSecondaryParticleLocatorBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::SecondaryParticleLocatorBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleLocatorBlock",
    "The continuous energy IXS block with the secondary particle locators\n\n"
    "The SecondaryParticleLocatorBlock class contains 10 locators for each\n"
    "secondary particle type as given on the PTYPE block.\n"
    "The number of available particle types is stored in NXS(7)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< std::array< unsigned int, 10 > > >(),
    python::arg( "locators" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self       the block\n"
    "    locators   the locators for each particle type"
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

    "LLOC",
    &Block::LLOC,
    python::arg( "particle" ), python::arg( "index" ),
    "The locator for a secondary particle index and block index\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    particle    the secondary particle index (one-based)"
    "    index       the block index (one-based)"
  )
  .def(

    "locator",
    &Block::locator,
    python::arg( "particle" ), python::arg( "index" ),
    "The locator for a secondary particle index and block index\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    particle    the secondary particle index (one-based)"
    "    index       the block index (one-based)"
  )
  .def(

    "HPD",
    &Block::HPD,
    python::arg( "index" ),
    "The locator to the HPD block for a secondary particle index\n\n"
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

    "YP",
    &Block::YP,
    python::arg( "index" ),
    "The locator to the YP block for a secondary particle index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the secondary particle index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
