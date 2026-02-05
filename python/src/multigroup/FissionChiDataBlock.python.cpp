// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/FissionChiDataBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapFissionChiDataBlock( python::module& module,
                                          python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::FissionChiDataBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "FissionChiDataBlock",
    "The multigroup fission fraction (PFNS) section block\n\n"
    "The FissionChiDataBlock class contains 1 array: \n"
    "  - the fission fraction (PFNS) for each group \n"
    "The size the array (the total number of energy groups) is stored in NXS(5). \n\n"
    "Parameters\n"
    "----------\n"
    "    fission_fraction : list of float \n "
    "        the fission fraction (PFNS) for each group\n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "fission_fraction" ),
    "Create the CHI block with the fission fraction values \n\n"
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

    "FISFR",
    [] ( const Block& self ) -> DoubleRange
       { return self.FISFR(); },
    "The fission fraction (PFNS) values"
  )
  .def_property_readonly(

    "fission_fraction",
    [] ( const Block& self ) -> DoubleRange
       { return self.fissionFraction(); },
    "The fission fraction (PFNS) values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
