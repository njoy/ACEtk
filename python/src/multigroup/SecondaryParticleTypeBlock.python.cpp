// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/SecondaryParticleTypeBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapSecondaryParticleTypeBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::SecondaryParticleTypeBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleTypeBlock",
    "The multigroup IPT block with the secondary particle types\n\n"
    "The SecondaryParticleTypeBlock class contains the secondary particle types\n"
    "for which data is available. The allowed particle types are: \n"
    "    1  -  neutron \n"
    "    2  -  photon \n"
    "The number of available particle types is stored in NXS(8).\n\n"
    "Parameters\n"
    "----------\n"
    "    types : list of int \n"
    "        the secondary particle types\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int > >(),
    python::arg( "types" ),
    "Create the IPT block\n\n"
  )
  .def_property_readonly(

    "NTYPE",
    &Block::NTYPE,
    "The number of secondary particle types"
  )
  .def_property_readonly(

    "number_secondary_particle_types",
    &Block::numberSecondaryParticleTypes,
    "The number of secondary particle types"
  )
  .def(

    "IPT",
    &Block::IPT,
    python::arg( "index" ),
    "The particle type for a secondary particle index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int \n"
    "        the index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The particle type \n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        When the index is out of range \n\n"
  )
  .def(

    "particle_type",
    &Block::particleType,
    python::arg( "index" ),
    "The particle type for a secondary particle index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int \n"
    "        the index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The particle type \n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        When the index is out of range \n\n"
  )
  .def_property_readonly(

    "IPTs",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.IPTs(); },
    "The particle types"
  )
  .def_property_readonly(

    "particle_types",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.particleTypes(); },
    "The particle types"
  )
  .def(

    "has_IPT",
    &Block::hasIPT,
    python::arg( "type" ),
    "Return whether or not the particle type is present\n\n"
    "Parameters\n"
    "----------\n"
    "    type : int \n"
    "        the particle type\n\n"
    "Returns\n"
    "-------\n"
    "    bool \n"
    "        Whether or not the particle type is present \n\n"
  )
  .def(

    "has_particle_type",
    &Block::hasParticleType,
    python::arg( "type" ),
    "Return whether or not the particle type is present\n\n"
    "Parameters\n"
    "----------\n"
    "    type : int \n"
    "        the particle type\n\n"
    "Returns\n"
    "-------\n"
    "    bool \n"
    "        Whether or not the particle type is present \n\n"
  )
  .def(

    "index",
    &Block::index,
    python::arg( "type" ),
    "Return the index (one-based) of the particle type\n\n"
    "Parameters\n"
    "----------\n"
    "    type : int \n"
    "        The particle type \n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The index of the particle type (one-based) \n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        When the particle type is not present \n\n"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
