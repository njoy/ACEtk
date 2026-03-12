// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/P0LocatorBlock.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapP0LocatorBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::P0LocatorBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "P0LocatorBlock",
    "The multigroup P0L block with locators for P0 blocks\n"
    "for the incident and secondary particle(s)\n\n"
    "The P0LocatorBlock class contains NSEC+1 locators, one for the incident particle\n"
    "and one for each secondary particle type given in the :class:`SecondaryParticleTypeBlock`. \n"
    "The first locator is for the incident particle and the remaining are for the secondary \n"
    "particles, in the same order as they are in the :class:`SecondaryParticleTypeBlock`.\n\n"
    "The number of secondary particle types, NSEC, is stored in NXS(8).\n\n"
    "Parameters\n"
    "----------\n"
    "    locators : list of int \n"
    "        the locators for each P0 block\n\n"
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

    "P02",
    &Block::P02,
    python::arg( "particle" ),
    "Return the locator for the P0 block for a secondary particle index  \n\n"
    "Parameters\n"
    "----------\n"
    "    particle : int \n"
    "        the secondary particle index (one-based) in the IPT block\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The locator\n"
  )
  .def(

    "secondary_locator",
    &Block::secondaryLocator,
    python::arg( "particle" ),
    "Return the locator for the P0 block for a secondary particle index  \n\n"
    "Parameters\n"
    "----------\n"
    "    particle : int \n"
    "        the secondary particle index (one-based) in the IPT block\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The locator\n"
  )
  .def(

    "P01",
    &Block::P01,
    "Return the locator for the P0 block for the incident particle  \n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The locator\n"
  )
  .def(

    "incident_locator",
    &Block::incidentLocator,
    "Return the locator for the P0 block for the incident particle  \n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The locator\n"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
