// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/PhotoNuclearTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapPhotoNuclearTable( python::module& module, python::module& ) {

  // type aliases
  using Header = njoy::ACEtk::Table::Header;
  using Table = njoy::ACEtk::PhotoNuclearTable;
  using MTR = njoy::ACEtk::block::MTR;
  using LQR = njoy::ACEtk::block::LQR;
  using SIG = njoy::ACEtk::block::SIG;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "PhotoNuclearTable",
    "A continuous energy ACE table\n\n"
    "The PhotoNuclearTable class represents the ACE table for the photonuclear data."
  );

  // wrap the table
  table
//  .def(
//
//    python::init< unsigned int, unsigned int, Header,
//                  ESZ, std::optional< NU >, std::optional< DNU >,
//                  MTR, LQR, SIG, AND, DLW,
//                  std::optional< BDD >, std::optional< DNED >,
//                  std::optional< GPD >, std::optional< MTRP >,
//                  std::optional< SIGP >, std::optional< ANDP >,
//                  std::optional< DLWP >, std::optional< YP >,
//                  std::optional< UNR >, std::optional< PTYPE >,
//                  std::optional< std::vector< HPD > >,
//                  std::optional< std::vector< MTRH > >,
//                  std::optional< std::vector< SIGH > >,
//                  std::optional< std::vector< ANDH > >,
//                  std::optional< std::vector< DLWH > >,
//                  std::optional< std::vector< YH > > >(),
//    python::arg( "z" ), python::arg( "a" ),
//    python::arg( "header" ), python::arg( "esz" ),
//    python::arg( "nu" ) = std::nullopt, python::arg( "dnu" ) = std::nullopt,
//    python::arg( "mtr" ), python::arg( "lqr" ),
//    python::arg( "sig" ), python::arg( "ang" ), python::arg( "dlw" ),
//    python::arg( "bdd" ) = std::nullopt, python::arg( "dned" ) = std::nullopt,
//    python::arg( "gpd" ) = std::nullopt, python::arg( "mtrp" ) = std::nullopt,
//    python::arg( "sigp" ) = std::nullopt, python::arg( "andp" ) = std::nullopt,
//    python::arg( "dlwp" ) = std::nullopt, python::arg( "yp" ) = std::nullopt,
//    python::arg( "unr" ) = std::nullopt, python::arg( "ptype" ) = std::nullopt,
//    python::arg( "hpd" ) = std::nullopt, python::arg( "mtrh" ) = std::nullopt,
//    python::arg( "sigh" ) = std::nullopt,
//    python::arg( "andh" ) = std::nullopt, python::arg( "dlwh" ) = std::nullopt,
//    python::arg( "yh" ) = std::nullopt,
//    "Initialise the table\n\n"
//    "Arguments:\n"
//    "    self      the table\n"
//    "    z         the Z number of the nuclide\n"
//    "    a         the A number of the nuclide\n"
//    "    header    the header for the table\n"
//    "    esz       the principal cross section block\n"
//    "    nu        the optional fission neutron multiplicity block\n"
//    "    dnu       the optional delayed fission neutron multiplicity block\n"
//    "    mtr       the reaction number block\n"
//    "    lqr       the reaction Q value block\n"
//    "    sig       the cross section data block\n"
//    "    ang       the angular distribution data block\n"
//    "    dlw       the energy distribution data block\n"
//    "    bdd       the delayed fission neutron precursor data block\n"
//    "    dned      the delayed fission neutron energy distribution data block\n"
//    "    gpd       the photon production block\n"
//    "    mtrp      the photon production reaction number block\n"
//    "    sigp      the photon production cross section data block\n"
//    "    angp      the photon production angular distribution data block\n"
//    "    dlwp      the photon production energy distribution data block\n"
//    "    yp        the photon multiplicity reaction number block\n"
//    "    unr       the unresolved resonance probability table block\n"
//    "    ptype     the secondary particle type block\n"
//    "    hpd       the secondary particle production blocks\n"
//    "    mtrh      the secondary particle production reaction number blocks\n"
//    "    sigh      the secondary particle production cross section data blocks\n"
//    "    angh      the secondary particle angular distribution data blocks\n"
//    "    dlwh      the secondary particle energy distribution data blocks\n"
//    "    yh        the secondary particle multiplicity reaction number blocks"
//  )
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
    "The number of available reactions"
  )
  .def_property_readonly(

    "number_reactions",
    &Table::numberReactions,
    "The number of available reactions"
  )
  .def_property_readonly(

    "NTYPE",
    &Table::NTYPE,
    "The number of secondary particle types"
  )
  .def_property_readonly(

    "number_secondary_particle_types",
    &Table::numberSecondaryParticleTypes,
    "The number of secondary particle types"
  )
//  .def_property_readonly(
//
//    "ESZ",
//    &Table::ESZ,
//    "The principal cross section block"
//  )
//  .def_property_readonly(
//
//    "principal_cross_section_block",
//    &Table::principalCrossSectionBlock,
//    "The principal cross section block"
//  )
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

    "SIG",
    &Table::SIG,
    "The cross section block"
  )
  .def_property_readonly(

    "cross_section_block",
    &Table::crossSectionBlock,
    "The cross section block"
  );

  // add standard block definitions
  addStandardTableDefinitions< Table >( table );
}
