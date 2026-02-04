// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/TotalCrossSectionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapTotalCrossSectionBlock( python::module& module,
                                          python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::TotalCrossSectionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TotalCrossSectionBlock",
    "The multigroup total cross section block\n\n"
    " The TotalCrossSectionBlock class contains 1 array: \n"
    "   - total cross section for each group \n"
    " The size the array (the total number of energy groups) is stored in NXS(5). \n\n"
    "Parameters\n"
    "----------\n"
    "    totalCrossSection : list of float \n "
    "        the total cross section for each group\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "total_cross_section" ),
    "Create the TOT block with the total cross section values \n\n"
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

    "SIGTOT",
    [] ( const Block& self ) -> DoubleRange
       { return self.SIGTOT(); },
    "The total cross section values"
  )
  .def_property_readonly(

    "total_cross_section",
    [] ( const Block& self ) -> DoubleRange
       { return self.totalCrossSection(); },
    "The total cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
