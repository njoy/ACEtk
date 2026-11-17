// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/multigroup/SecondaryParticleGroupStructureBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapSecondaryParticleGroupStructureBlock( python::module& module,
                                          python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::multigroup::SecondaryParticleGroupStructureBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "SecondaryParticleGroupStructureBlock",
    "The multigroup secondary particle group structure block\n\n"
    "The SecondaryParticleGroupStructureBlock class contains 2 arrays of the same length:\n"
    "  - the mean energies of each group (in MeV)\n"
    "  - the widths of each group (in MeV)\n"
    "The size of each (the total number of energy groups), NERG, is LERG2(i).\n\n"
    "Parameters\n"
    "----------\n"
    "    group_means : list of floats \n"
    "        the mean energies of each group in MeV \n"
    "    group_widths : list of floats \n"
    "        the widths of each group in MeV \n\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "group_means" ), python::arg( "group_widths" ),
    "Create the ERG2 block with group means and widths \n\n"
  )
  .def_property_readonly(

    "NERG",
    &Block::NERG,
    "The number of energy groups"
  )
  .def_property_readonly(

    "number_energy_groups",
    &Block::numberEnergyGroups,
    "The number of energy groups"
  )
  .def_property_readonly(

    "ECENT2",
    [] ( const Block& self ) -> DoubleRange
       { return self.groupMeans(); },
    "The mean energies of each group in MeV"
  )
  .def_property_readonly(

    "group_means",
    [] ( const Block& self ) -> DoubleRange
       { return self.groupMeans(); },
    "The mean energies of each group in MeV"
  )
  .def_property_readonly(

    "EWID2",
    [] ( const Block& self ) -> DoubleRange
       { return self.groupWidths(); },
    "The widths of each group MeV"
  )
  .def_property_readonly(

    "group_widths",
    [] ( const Block& self ) -> DoubleRange
       { return self.groupWidths(); },
    "The widths of each group MeV"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // multigroup namespace
