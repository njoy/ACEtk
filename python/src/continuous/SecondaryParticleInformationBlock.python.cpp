// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/SecondaryParticleInformationBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapSecondaryParticleInformationBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::SecondaryParticleInformationBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleInformationBlock",
    "The continuous energy NTRO block with the number of reactions for each "
    "secondary particle type\n\n"
    "The SecondaryParticleInformationBlock class contains the number of reactions\n"
    "that produce each secondary particle type as given on the PTYPE.\n"
    "The number of available particle types is stored in NXS(7)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int > >(),
    python::arg( "numbers" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self       the block\n"
    "    numbers    the number of reaction for each particle type"
  )
  .def_property_readonly(

    "NTYPE",
    &Block::NTYPE,
    "The number of secondary particle types (excluding the projectile and photons)"
  )
  .def_property_readonly(

    "number_additional_secondary_particle_types",
    &Block::numberAdditionalSecondaryParticleTypes,
    "The number of secondary particle types (excluding the projectile and photons)"
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
  .def_property_readonly(

    "NPs",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.NPs(); },
    "The number of reactions for each particle type"
  )
  .def_property_readonly(

    "number_reactions",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.numberReactions(); },
    "The number of reactions for each particle type"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
