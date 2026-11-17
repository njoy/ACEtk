// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/XPNLocatorBlock.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapXPNLocatorBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::XPNLocatorBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "XPNLocatorBlock",
    "The multigroup XPNL block with locators for the XPN blocks \n"
    "for the incident and secondary particles\n\n"
    "The XPNLocatorBlock class contains NSEC+1 locators, one for the incident particle\n"
    "and one for each secondary particle type given in the :class:`SecondaryParticleTypeBlock`. \n"
    "The first locator is for the incident particle and the remaining are for the secondary \n"
    "particles, in the same order as they are in the :class:`SecondaryParticleTypeBlock`. The \n"
    "locators point to the XPN blocks, which contain relative locators within the PN blocks.\n\n"
    "The number of secondary particle types, NSEC, is stored in NXS(8).\n\n"
    "Parameters\n"
    "----------\n"
    "    locators : list of int \n"
    "        the locators for each XPN block\n\n"
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

    "LXPN",
    &Block::LXPN,
    python::arg( "particle" ),
    "Return the locator for the XPN block for a secondary particle index  \n\n"
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
    "Return the locator for the XPN block for a secondary particle index  \n\n"
    "Parameters\n"
    "----------\n"
    "    particle : int \n"
    "        the secondary particle index (one-based) in the IPT block\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The locator\n"
  )
  .def_property_readonly(

    "LXPN1",
    &Block::LXPN1,
    "The locator for the XPN block for the incident particle  \n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The locator\n"
  )
  .def_property_readonly(

    "incident_locator",
    &Block::incidentLocator,
    "The locator for the XPN block for the incident particle  \n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The locator\n"
  )
  .def(

    "is_isotropic",
    &Block::isIsotropic,
    python::arg( "particle" ),
    "Whether or not the secondary particle angular distribution is isotropic  \n\n"
    "Parameters\n"
    "----------\n"
    "    particle : int \n"
    "        the secondary particle index (one-based) in the IPT block\n\n"
    "Returns\n"
    "-------\n"
    "    bool \n"
    "        If the angular distribution is isotropic\n"
  )
  .def_property_readonly(

    "incident_isotropic",
    &Block::incidentIsotropic,
    "Whether or not the incident particle outgoing angular distribution is isotropic  \n\n"
    "Returns\n"
    "-------\n"
    "    bool \n"
    "        If the angular distribution is isotropic\n"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
