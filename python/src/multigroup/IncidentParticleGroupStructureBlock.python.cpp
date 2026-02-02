// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/IncidentParticleGroupStructureBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapIncidentParticleGroupStructureBlock( python::module& module,
                                          python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::IncidentParticleGroupStructureBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "IncidentParticleGroupStructureBlock",
    "The multigroup group structure block\n\n"
    " The IncidentParticleGroupStructureBlock class contains 2 arrays of the same length:\n"
    "   - the mean energies of each group (in MeV)\n"
    "   - the widths of each group (in MeV)\n"
    " The size of each (the total number of energy points) is stored in NXS(5).\n\n"
    "Parameters\n"
    "----------\n"
    "    group_means : list of floats \n"
    "        the mean energies of each group in MeV \n"
    "    group_widths : list of floats \n"
    "        the widths of each group in MeV \n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "group_means" ), python::arg( "group_widths" ),
    "Create the ERG block with group means and widths \n\n"
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

    "group_means",
    [] ( const Block& self ) -> DoubleRange
       { return self.groupMeans(); },
    "The group means in MeV"
  )
  .def_property_readonly(

    "group_widths",
    [] ( const Block& self ) -> DoubleRange
       { return self.groupWidths(); },
    "The group widths in MeV"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
