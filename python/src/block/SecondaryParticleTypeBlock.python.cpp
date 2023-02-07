// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/SecondaryParticleTypeBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapSecondaryParticleTypeBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::SecondaryParticleTypeBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleTypeBlock",
    "The continuous energy PTYPE block with the secondary particle types\n\n"
    "The SecondaryParticleTypeBlock class contains the secondary particle types\n"
    "for which data is available (excluding the incident particle type).\n"
    "The number of available available particle types is stored in NXS(7)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int >&& >(),
    python::arg( "types" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    types    the particle types"
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
  .def_property_readonly(

    "IPs",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.IPs(); },
    "The particle types"
  )
  .def_property_readonly(

    "particle_types",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.particleTypes(); },
    "The particle types"
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

} // block namespace
