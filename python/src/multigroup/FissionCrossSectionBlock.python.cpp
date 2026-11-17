// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/FissionCrossSectionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapFissionCrossSectionBlock( python::module& module,
                                          python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::FissionCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "FissionCrossSectionBlock",
    "The multigroup fission cross section block\n\n"
    "The FissionCrossSectionBlock class contains 1 array: \n"
    "  - fission cross section for each group \n"
    "The size the array (the total number of energy groups) is stored in NXS(5). \n\n"
    "Parameters\n"
    "----------\n"
    "    fission_cross_section : list of float \n "
    "        the fission cross section for each group\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "fission_cross_section" ),
    "Create the FISS block with the fission cross section values \n\n"
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

    "SIGFISS",
    [] ( const Block& self ) -> DoubleRange
       { return self.SIGFISS(); },
    "The fission cross section values"
  )
  .def_property_readonly(

    "fission_cross_section",
    [] ( const Block& self ) -> DoubleRange
       { return self.fissionCrossSection(); },
    "The fission cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
