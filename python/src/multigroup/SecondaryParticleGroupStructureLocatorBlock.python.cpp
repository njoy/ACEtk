// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/SecondaryParticleGroupStructureLocatorBlock.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapSecondaryParticleGroupStructureLocatorBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::SecondaryParticleGroupStructureLocatorBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleGroupStructureLocatorBlock",
    "The multigroup ERG2L block with locators for the group structure block(s)\n"
    "for the secondary particle(s)\n\n"
    "The SecondaryParticleGroupStructureLocatorBlock class contains NSEC locators, one for each\n"
    "secondary particle type given in the IPT block.\n"
    "The number of secondary particle types is stored in NXS(8).\n\n"
    "Parameters\n"
    "----------\n"
    "    locators : list of int \n"
    "        the locators for each secondary particle type\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int > >(),
    python::arg( "locators" ),
    "Create the block\n\n"
  )
  .def_property_readonly(

    "NSEC",
    &Block::NSEC,
    "The number of secondary particle types"
  )
  .def_property_readonly(

    "number_secondary_particle_types",
    &Block::numberSecondaryParticleTypes,
    "The number of secondary particle types"
  )
  .def(

    "ERG2",
    &Block::ERG2,
    python::arg( "particle" ),
    "The locator for a secondary particle index \n\n"
    "Parameters\n"
    "----------\n"
    "    particle : int \n"
    "        the secondary particle index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The locator"
  )
  .def(

    "locator",
    &Block::locator,
    python::arg( "particle" ),
    "The locator for a secondary particle index \n\n"
    "Parameters\n"
    "----------\n"
    "    particle : int \n"
    "        the secondary particle index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The locator"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
