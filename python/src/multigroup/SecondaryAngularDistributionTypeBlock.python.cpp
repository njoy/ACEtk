// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/SecondaryAngularDistributionTypeBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapSecondaryAngularDistributionTypeBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::SecondaryAngularDistributionTypeBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryAngularDistributionTypeBlock",
    "The multigroup SANG2 block with the secondary particle angular distribution types\n\n"
    "The SecondaryAngularDistributionTypeBlock class contains the secondary angular distribution \n"
    "types. The allowed particle types are: \n\n"
    "    0  -  equi-probable cosines \n"
    "    1  -  discrete cosines \n\n"
    "The number of secondary particle types (NSEC) is stored in NXS(8).\n\n"
    "Parameters\n"
    "----------\n"
    "    types : list of int \n"
    "        the secondary angular distribution types\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< unsigned int > >(),
    python::arg( "types" ),
    "Create the SANG2 block\n\n"
  )
  .def_property_readonly(

    "NSEC",
    &Block::NSEC,
    "The number of secondary particles"
  )
  .def_property_readonly(

    "number_secondary_particles",
    &Block::numberSecondaryParticles,
    "The number of secondary particles"
  )
  .def(

    "SANG2",
    &Block::SANG2,
    python::arg( "index" ),
    "The angular distribution type for a secondary particle index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int \n"
    "        the index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The angular distribution type \n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        When the index is out of range \n\n"
  )
  .def(

    "distribution_type",
    &Block::distributionType,
    python::arg( "index" ),
    "The angular distribution type for a secondary particle index\n\n"
    "Parameters\n"
    "----------\n"
    "    index : int \n"
    "        the index (one-based)\n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The angular distribution type \n\n"
    "Raises\n"
    "------\n"
    "    Exception \n"
    "        When the index is out of range \n\n"
  )
  .def_property_readonly(

    "SANG2s",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.SANG2s(); },
    "The particle types"
  )
  .def_property_readonly(

    "distribution_types",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.distributionTypes(); },
    "The particle types"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
