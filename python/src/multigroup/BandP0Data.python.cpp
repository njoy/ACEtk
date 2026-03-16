// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/BandP0Data.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapBandP0Data( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::BandP0Data;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "BandP0Data",
    "P0 Block for the incident particle\n\n"
    "The BandP0Data class contains the P0 block for the outgoing\n"
    "particle when it is the same as the incident particle. It is \n"
    "stored as a Square Band Matrix. Down-scatter groups are the\n"
    "super-diagonals in the matrix and up-scatter groups are the\n"
    "sub-diagonals in the matrix because the energy groups are\n"
    "sorted in descending order.\n\n"
    "Parameters\n"
    "----------\n"
    "    matrix : array-like \n"
    "        the two-dimensional matrix data values \n"
    "    down : int \n"
    "        the number of down-scatter groups \n"
    "    up : int \n"
    "        the number of up-scatter groups \n\n"
    "Notes\n"
    "-----\n" 
    "Any non-zero values in the matrix outside of the defined \n"
    "bands will be lost in the construction of the BandP0Data  \n"
    "object. \n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< std::vector< double > >,
                  unsigned int, unsigned int >(),
    python::arg( "matrix" ), python::arg( "down" ),
    python::arg( "up" ),
    "Create the block\n\n"
  )
  .def_property_readonly(
  
    "NGRP",
    &Block::NGRP,
    "The number of energy groups"
  )
  .def_property_readonly(
  
    "number_energy_groups",
    &Block::numberEnergyGroups,
    "The number energy groups"
  )
  .def_property_readonly(
  
    "NDS",
    &Block::NDS,
    "The number of down-scatter groups"
  )
  .def_property_readonly(
  
    "number_down_scatter_groups",
    &Block::numberDownScatterGroups,
    "The number of down-scatter groups"
  )  
  .def_property_readonly(
  
    "NUS",
    &Block::NUS,
    "The number of up-scatter groups"
  )
  .def_property_readonly(
  
    "number_up_scatter_groups",
    &Block::numberUpScatterGroups,
    "The number of up-scatter groups"
  )
  .def_property_readonly(
  
    "block_length",
    &Block::blockLength,
    "The length of the XSS block"
  )
  .def_property_readonly(
  
    "p0_matrix_list",
    [] ( const Block& self ) -> DoubleRange
       { return self.P0MatrixList(); },
    "The P0 matrix as a 1-D array"
  )
  .def(
  
    "group_down_scatter_groups",
    &Block::groupDownScatterGroups,
    python::arg( "group" ),
    "The number of down-scatter groups for a specific incident group\n\n"
    "Parameters\n"
    "----------\n"
    "    group : int \n "
    "        the incident group index (one-based) \n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The number of down-scatter groups for the incident group "
  )
  .def(
  
    "group_up_scatter_groups",
    &Block::groupUpScatterGroups,
    python::arg( "group" ),
    "The number of up-scatter groups for a specific incident group\n\n"
    "Parameters\n"
    "----------\n"
    "    group : int \n "
    "        the incident group index (one-based) \n\n"
    "Returns\n"
    "-------\n"
    "    int \n"
    "        The number of up-scatter groups for the incident group \n"
  )
  .def(
  
    "p0_value",
    &Block::P0Value,
    python::arg( "incident_group" ),
    python::arg( "outgoing_group" ),
    "The P0 matrix value for a specific incident and outgoing group pair.\n\n"
    "Parameters\n"
    "----------\n"
    "    incident_group : int \n "
    "        the incident group index (one-based) \n"
    "    outgoing_group : int \n "
    "        the outgoing group index (one-based) \n\n"
    "Returns\n"
    "-------\n"
    "    double \n"
    "        The P0 value for the groups \n"
  )
  .def(
  
    "incident_row",
    &Block::incidentRow,
    python::arg( "incident_group" ),
    "The row of the matrix for a specific incident group\n\n"
    "Parameters\n"
    "----------\n"
    "    incident_group : int \n "
    "        the incident group index (one-based) \n\n"
    "Returns\n"
    "-------\n"
    "    list of doubles \n"
    "        The matrix for for the incident group \n"
  )
  .def_property_readonly(
  
    "p0_matrix",
    [] ( const Block& self ) -> DoubleRange2D
       { return self.P0Matrix(); },
    "The P0 Matrix\n\n"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
