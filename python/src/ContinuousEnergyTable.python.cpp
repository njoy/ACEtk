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
  using Header = njoy::ACEtk::Table::Header;
  using Table = njoy::ACEtk::ContinuousEnergyTable;
  using ESZ = njoy::ACEtk::block::ESZ;
  using NU = njoy::ACEtk::block::NU;
  using MTR = njoy::ACEtk::block::MTR;
  using LQR = njoy::ACEtk::block::LQR;
  using TYR = njoy::ACEtk::block::TYR;
  using SIG = njoy::ACEtk::block::SIG;
  using AND = njoy::ACEtk::block::AND;
  using DLW = njoy::ACEtk::block::DLW;

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
  .def(

    python::init< unsigned int, unsigned int, Header,
                  ESZ, std::optional< NU >, MTR, LQR, TYR,
                  SIG, AND, DLW >(),
    python::arg( "z" ), python::arg( "a" ),
    python::arg( "header" ), python::arg( "esz" ),
    python::arg( "nu" ) = std::nullopt,
    python::arg( "mtr" ), python::arg( "lqr" ), python::arg( "tyr" ),
    python::arg( "sig" ), python::arg( "ang" ), python::arg( "dlw" ),
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    z         the Z number of the nuclide\n"
    "    a         the A number of the nuclide\n"
    "    header    the header for the table\n"
    "    esz       the principal cross section block\n"
    "    nu        the optional fission multiplicity block\n"
    "    mtr       the reaction number block\n"
    "    lqr       the reaction Q value block\n"
    "    tyr       the reference frame and multiplicity block\n"
    "    sig       the cross section data block\n"
    "    ang       the angular distribution data block\n"
    "    dlw       the energy distribution data block"
  )
  .def_property_readonly(

    "zaid",
    &Table::ZAID,
    "The full ZAID or SZAID of the table"
  )
  .def_property_readonly(

    "AWR",
    &Table::AWR,
    "The atomic weight ratio (with respect to the neutron mass)"
  )
  .def_property_readonly(

    "atomic_weight_ratio",
    &Table::atomicWeightRatio,
    "The atomic weight ratio (with respect to the neutron mass)"
  )
  .def_property_readonly(

    "TEMP",
    &Table::TEMP,
    "The temperature of the table"
  )
  .def_property_readonly(

    "temperature",
    &Table::temperature,
    "The temperature of the table"
  )
  .def_property_readonly(

    "date",
    &Table::date,
    "The date"
  )
  .def_property_readonly(

    "title",
    &Table::title,
    "The title"
  )
  .def_property_readonly(

    "material",
    &Table::material,
    "The material"
  )
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

    "number_projectile_production_reactions",
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

    "ESZ",
    &Table::ESZ,
    "The principal cross section block"
  )
  .def_property_readonly(

    "principal_cross_section_block",
    &Table::principalCrossSectionBlock,
    "The principal cross section block"
  )
  .def_property_readonly(

    "MTR",
    &Table::MTR,
    "The reaction number block"
  )
  .def_property_readonly(

    "reaction_number_block",
    &Table::reactionNumberBlock,
    "The reaction number block"
  )
  .def_property_readonly(

    "LQR",
    &Table::LQR,
    "The reaction Q value block"
  )
  .def_property_readonly(

    "reaction_qvalue_block",
    &Table::reactionQValueBlock,
    "The reaction Q value block"
  )
  .def_property_readonly(

    "TYR",
    &Table::TYR,
    "The reference frame and multiplicity block"
  )
  .def_property_readonly(

    "frame_and_multiplicity_block",
    &Table::frameAndMultiplicityBlock,
    "The reference frame and multiplicity block"
  )
  .def_property_readonly(

    "SIG",
    &Table::SIG,
    "The cross section block"
  )
  .def_property_readonly(

    "cross_section_block",
    &Table::crossSectionBlock,
    "The cross section block"
  )
  .def_property_readonly(

    "AND",
    &Table::AND,
    "The angular distribution block"
  )
  .def_property_readonly(

    "angular_distribution_block",
    &Table::angularDistributionBlock,
    "The angular distribution block"
  )
  .def_property_readonly(

    "DLW",
    &Table::DLW,
    "The energy distribution block"
  )
  .def_property_readonly(

    "energy_distribution_block",
    &Table::energyDistributionBlock,
    "The energy distribution block"
  )
  .def_property_readonly(

    "MTRP",
    &Table::MTRP,
    "The photon production reaction number block"
  )
  .def_property_readonly(

    "photon_production_reaction_number_block",
    &Table::photonProductionReactionNumberBlock,
    "The production reaction reaction number block"
  )
  .def_property_readonly(

    "ANDP",
    &Table::ANDP,
    "The photon production angular distribution block"
  )
  .def_property_readonly(

    "photon_production_angular_distribution_block",
    &Table::photonProductionAngularDistributionBlock,
    "The photon production angular distribution block"
  )
  .def_property_readonly(
    "PTYPE",
    &Table::PTYPE,
    "The secondary particle type block"
  )
  .def_property_readonly(

    "secondary_particle_type_block",
    &Table::secondaryParticleTypeBlock,
    "The secondary particle type block"
  );

  // add standard block definitions
  addStandardTableDefinitions< Table >( table );
}
