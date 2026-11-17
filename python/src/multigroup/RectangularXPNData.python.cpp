// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/RectangularXPNData.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapRectangularXPNData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::RectangularXPNData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "RectangularXPNData",
    "XPN Block for outgoing particles that are not the incident particle\n\n"
    "The RectangularXPNData class contains the XPN block for the outgoing\n"
    "particle when it is not the incident particle. \n\n"
    "Parameters\n"
    "----------\n"
    "    matrix : array-like of int \n"
    "        the two-dimensional matrix data values \n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< std::vector< int > > >(),
    python::arg( "matrix" ),
    "Create the block\n\n"
  )
  .def_property_readonly(
  
    "NGRP",
    &Block::NGRP,
    "The number of incident energy groups"
  )
  .def_property_readonly(
  
    "number_incident_energy_groups",
    &Block::numberIncidentEnergyGroups,
    "The number of incident energy groups"
  )
  .def_property_readonly(
  
    "NERG",
    &Block::NERG,
    "The number of outgoing energy groups"
  )
  .def_property_readonly(
  
    "number_outgoing_energy_groups",
    &Block::numberOutgoingEnergyGroups,
    "The number of outgoing energy groups"
  )
  .def_property_readonly(
  
    "block_length",
    &Block::blockLength,
    "The length of the XSS block"
  )
  .def_property_readonly(
  
    "xpn_matrix_list",
    [] ( const Block& self ) -> DoubleRange
       { return self.XPNMatrixList(); },
    "The XPN matrix as a 1-D array"
  )
  .def(
  
    "LPND",
    &Block::LPND,
    python::arg( "incident_group" ),
    python::arg( "outgoing_group" ),
    "The locator for a specific incident and outgoing group pair.\n\n"
    "Parameters\n"
    "----------\n"
    "    incident_group : int \n "
    "        the incident group index (one-based) \n"
    "    outgoing_group : int \n "
    "        the outgoing group index (one-based) \n\n"
    "Returns\n"
    "-------\n"
    "    double \n"
    "        The XPN value for the groups \n"
  )
  .def(
  
    "locator",
    &Block::locator,
    python::arg( "incident_group" ),
    python::arg( "outgoing_group" ),
    "The locator for a specific incident and outgoing group pair.\n\n"
    "Parameters\n"
    "----------\n"
    "    incident_group : int \n "
    "        the incident group index (one-based) \n"
    "    outgoing_group : int \n "
    "        the outgoing group index (one-based) \n\n"
    "Returns\n"
    "-------\n"
    "    double \n"
    "        The XPN value for the groups \n"
  )
  .def(
  
    "incident_row",
    [] ( const Block& self, unsigned int incident_group ) -> DoubleRange
       { return self.incidentRow( incident_group ); },
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
  .def(
  
    "outgoing_column",
    [] ( const Block& self, unsigned int outgoing_group ) -> DoubleRange
       { return self.outgoingColumn( outgoing_group ); },
    python::arg( "outgoing_group" ),
    "The column of the matrix for a specific outgoing group\n\n"
    "Parameters\n"
    "----------\n"
    "    outgoing_group : int \n "
    "        the outgoing group index (one-based) \n\n"
    "Returns\n"
    "-------\n"
    "    list of doubles \n"
    "        The matrix for for the incident group \n"
  )
  .def_property_readonly(
  
    "xpn_matrix",
    [] ( const Block& self ) -> DoubleRange2D
       { return self.XPNMatrix(); },
    "The XPN Matrix\n\n"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
