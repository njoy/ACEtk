// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/ContinuousEnergyTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapContinuousEnergyTable( python::module& module, python::module& ) {

  // type aliases
  using Table = njoy::ACEtk::ContinuousEnergyTable;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "ContinuousEnergyTable",
    "A continuous energy ACE table\n\n"
    "The ContinuousEnergyTable class represents the ACE table for continuous\n"
    "energy data for incident neutrons and charged particles."
  );

  // wrap the table
  table
//  .def(
//
//    python::init< Header&&, Data&& >(),
//    python::arg( "header" ), python::arg( "data" ),
//    "Initialise the table\n\n"
//    "Arguments:\n"
//    "    self     the table\n"
//    "    header   the header information\n"
//    "    data     the ACE data"
//  )
  .def_property_readonly(

    "length",
    &Table::length,
    "The total length of the XSS array"
  )
  .def_property_readonly(

    "za",
    &Table::ZA,
    "The ZA of the target"
  )
  .def_property_readonly(

    "NES",
    &Table::NES,
    "The number of energy points"
  )
  .def_property_readonly(

    "number_energy_points",
    &Table::numberEnergyPoints,
    "The number of energy points"
  )
  .def_property_readonly(

    "NTR",
    &Table::NTR,
    "The number of available reactions (excluding elastic)"
  )
  .def_property_readonly(

    "number_reactions",
    &Table::numberReactions,
    "The number of available reactions (excluding elastic)"
  )
  .def_property_readonly(

    "total_number_reactions",
    &Table::totalNumberReactions,
    "The total number of available reactions (including elastic)"
  )
  .def_property_readonly(

    "NR",
    &Table::NR,
    "The number of reactions excluding elastic that produce the projectile"
  )
  .def_property_readonly(

    "number_projectile_production_reactions_excluding_elastic",
    &Table::numberProjectileProductionReactions,
    "The number of reactions excluding elastic that produce the projectile"
  )
  .def_property_readonly(

    "NTRP",
    &Table::NTRP,
    "The number of reactions that produce photons"
  )
  .def_property_readonly(

    "number_photon_production_reactions",
    &Table::numberPhotonProductionReactions,
    "The number of reactions that produce photons"
  )
  .def_property_readonly(

    "NTYPE",
    &Table::NTYPE,
    "The number of secondary particle types (excluding the projectile)"
  )
  .def_property_readonly(

    "number_additional_secondary_particle_types",
    &Table::numberAdditionalSecondaryParticleTypes,
    "The number of secondary particle types (excluding the projectile)"
  )
  .def_property_readonly(

    "NPCR",
    &Table::NPCR,
    "The number of delayed percursor families"
  )
  .def_property_readonly(

    "number_delayed_precursors",
    &Table::numberDelayedPrecursors,
    "The number of delayed percursor families"
  )
  .def_property_readonly(

    "S",
    &Table::S,
    "The excited state of the target"
  )
  .def_property_readonly(

    "excited_state",
    &Table::excitedState,
    "The excited state of the target"
  )
  .def_property_readonly(

    "Z",
    &Table::Z,
    "The atom number of the target"
  )
  .def_property_readonly(

    "atom_number",
    &Table::atomNumber,
    "The atom number of the target"
  )
  .def_property_readonly(

    "A",
    &Table::A,
    "The mass number of the target"
  )
  .def_property_readonly(

    "mass_number",
    &Table::massNumber,
    "The mass number of the target"
  )
  .def_property_readonly(

    "esz",
    &Table::ESZ,
    "The principal cross section block"
  )
  .def_property_readonly(

    "principal_cross_section_block",
    &Table::principalCrossSectionBlock,
    "The principal cross section block"
  )
  //! @todo solve the header version print issue to add this to the table definitions instead
  .def(

    "to_file",
    [] ( const Table& self, const std::string& filename ) {

      std::ofstream out( filename );
      self.print< 1, 0, 0 >( out );
      out.close();
    },
    "Write the ACE table to a file\n\n"
    "Arguments:\n"
    "    self        the table\n"
    "    filename    the file name and path"
  );

  // add standard block definitions
  addStandardTableDefinitions< Table >( table );
}
