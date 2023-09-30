// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/PhotonuclearTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapPhotonuclearTable( python::module& module, python::module& ) {

  // type aliases
  using HeaderVariant = njoy::ACEtk::Table::HeaderVariant;
  using Table = njoy::ACEtk::PhotonuclearTable;
  using ESZU = njoy::ACEtk::photonuclear::ESZU;
  using MTR = njoy::ACEtk::continuous::MTR;
  using LQR = njoy::ACEtk::continuous::LQR;
  using SIG = njoy::ACEtk::continuous::SIG;
  using CrossSectionData = njoy::ACEtk::continuous::CrossSectionData;
  using MTRH = njoy::ACEtk::continuous::MTRH;
  using LQR = njoy::ACEtk::continuous::LQR;
  using SIGH = njoy::ACEtk::continuous::SIGH;
  using ANDH = njoy::ACEtk::continuous::ANDH;
  using DLWH = njoy::ACEtk::continuous::DLWH;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "PhotonuclearTable",
    "A continuous energy ACE table\n\n"
    "The PhotonuclearTable class represents the ACE table for the photonuclear data."
  );

  // wrap the table
  table
  .def(

    python::init< unsigned int, unsigned int, HeaderVariant,
                  ESZU, MTR, LQR, SIG,
                  std::optional< std::vector< unsigned int > >,
                  std::optional< std::vector< CrossSectionData > >,
                  std::optional< std::vector< CrossSectionData > >,
                  std::optional< std::vector< MTRH > >,
                  std::optional< std::vector< SIGH > >,
                  std::optional< std::vector< ANDH > >,
                  std::optional< std::vector< DLWH > > >(),
    python::arg( "z" ), python::arg( "a" ),
    python::arg( "header" ), python::arg( "eszu" ),
    python::arg( "mtr" ), python::arg( "lqr" ),
    python::arg( "sig" ),
    python::arg( "ptype" ) = std::nullopt, python::arg( "pxs" ) = std::nullopt,
    python::arg( "phn" ) = std::nullopt, python::arg( "mtrh" ) = std::nullopt,
    python::arg( "sigh" ) = std::nullopt,
    python::arg( "andh" ) = std::nullopt, python::arg( "dlwh" ) = std::nullopt,
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    z         the Z number of the nuclide\n"
    "    a         the A number of the nuclide\n"
    "    header    the header for the table\n"
    "    eszu      the principal cross section block\n"
    "    mtr       the reaction number block\n"
    "    lqr       the reaction Q value block\n"
    "    sig       the cross section data block\n"
    "    ptype     the secondary particle types\n"
    "    pxs       the secondary particle production cross section data\n"
    "    phn       the secondary particle heating cross section data\n"
    "    mtrh      the secondary particle production reaction number blocks\n"
    "    sigh      the secondary particle production cross section data blocks\n"
    "    andh      the secondary particle angular distribution data blocks\n"
    "    dlwh      the secondary particle energy distribution data blocks\n"
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
    "IXS",
    &Table::IXS,
    "The secondary particle information and locator block"
  )
  .def_property_readonly(

    "secondary_particle_locator_block",
    &Table::secondaryParticleLocatorBlock,
    "The secondary particle information and locator block"
  )
  .def(

    "PXS",
    &Table::PXS,
    python::arg( "index" ),
    "Return the secondary particle production cross section for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "secondary_particle_production_crossSection",
    &Table::secondaryParticleProductionCrossSection,
    python::arg( "index" ),
    "Return the secondary particle production cross section for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "PHN",
    &Table::PHN,
    python::arg( "index" ),
    "Return the secondary particle average heating cross section for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "secondary_particle_heating_cross_section",
    &Table::secondaryParticleHeatingCrossSection,
    python::arg( "index" ),
    "Return the secondary particle average heating cross section for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "MTRH",
    &Table::MTRH,
    python::arg( "index" ),
    "Return the reaction number block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "secondary_particle_reaction_number_block",
    &Table::secondaryParticleReactionNumberBlock,
    python::arg( "index" ),
    "Return the reaction number block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "TYRH",
    &Table::TYRH,
    python::arg( "index" ),
    "Return the reference frame and multiplicity block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "secondary_particle_frame_and_multiplicity_block",
    &Table::secondaryParticleFrameAndMultiplicityBlock,
    python::arg( "index" ),
    "Return the reference frame and multiplicity block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "SIGH",
    &Table::SIGH,
    python::arg( "index" ),
    "Return the production cross section block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "secondary_particle_production_cross_section_block",
    &Table::secondaryParticleProductionCrossSectionBlock,
    python::arg( "index" ),
    "Return the production cross section block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "ANDH",
    &Table::ANDH,
    python::arg( "index" ),
    "Return the angular distribution block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "secondary_particle_angular_distribution_block",
    &Table::secondaryParticleAngularDistributionBlock,
    python::arg( "index" ),
    "Return the angular distribution block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "DLWH",
    &Table::DLWH,
    python::arg( "index" ),
    "Return the energy distribution block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "secondary_particle_energy_distribution_block",
    &Table::secondaryParticleEnergyDistributionBlock,
    python::arg( "index" ),
    "Return the energy distribution block for a secondary particle index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardTableDefinitions< Table >( table );
}
