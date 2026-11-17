// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/AbsorptionCrossSectionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapAbsorptionCrossSectionBlock( python::module& module,
                                          python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::AbsorptionCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "AbsorptionCrossSectionBlock",
    "The multigroup absorption cross section block\n\n"
    "The AbsorptionCrossSectionBlock class contains 1 array: \n"
    "  - absorption cross section for each group \n"
    "The size the array (the total number of energy groups) is stored in NXS(5). \n\n"
    "Parameters\n"
    "----------\n"
    "    absorption_cross_section : list of float \n "
    "        the absorption cross section for each group\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "absorption_cross_section" ),
    "Create the ABS block with the absorption cross section values \n\n"
  )  
  .def_property_readonly(

    "NGRP",
    &Block::NGRP,
    "The number of energy groups"
  )
  .def_property_readonly(

    "number_energy_groups",
    &Block::numberEnergyGroups,
    "The number of energy groups"
  )
  .def_property_readonly(

    "SIGABS",
    [] ( const Block& self ) -> DoubleRange
       { return self.SIGABS(); },
    "The absorption cross section values"
  )
  .def_property_readonly(

    "absorption_cross_section",
    [] ( const Block& self ) -> DoubleRange
       { return self.absorptionCrossSection(); },
    "The absorption cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
