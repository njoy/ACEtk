// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/PhotoatomicTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapPhotoatomicTable( python::module& module, python::module& ) {

  // type aliases
  using HeaderVariant = njoy::ACEtk::Table::HeaderVariant;
  using Table = njoy::ACEtk::PhotoatomicTable;
  using ESZG = njoy::ACEtk::photoatomic::ESZG;
  using JINC = njoy::ACEtk::photoatomic::JINC;
  using JCOH = njoy::ACEtk::photoatomic::JCOH;
  using JFLO = njoy::ACEtk::photoatomic::JFLO;
  using LHNM = njoy::ACEtk::photoatomic::LHNM;
  using EPS = njoy::ACEtk::electron::EPS;
  using SWD = njoy::ACEtk::photoatomic::SWD;
  using SUBSH = njoy::ACEtk::electron::SUBSH;
  using SPHEL = njoy::ACEtk::photoatomic::SPHEL;
  using XPROB = njoy::ACEtk::electron::XPROB;
  using ESZE = njoy::ACEtk::electron::ESZE;
  using EXCIT = njoy::ACEtk::electron::EXCIT;
  using ELAS = njoy::ACEtk::electron::ELAS;
  using EION = njoy::ACEtk::electron::EION;
  using BREME = njoy::ACEtk::electron::BREME;
  using BREML = njoy::ACEtk::electron::BREML;
  using SELAS = njoy::ACEtk::electron::SELAS;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "PhotoatomicTable",
    "A thermal scattering ACE table\n\n"
    "The PhotoatomicTable class represents the ACE table for photoatomic data."
  );

  // wrap the table
  table
  .def(

    python::init< unsigned int, HeaderVariant,
                  std::vector< unsigned int >, std::vector< double >,
                  ESZG, JINC, JCOH, LHNM, std::optional< JFLO >,
                  std::optional< EPS >, std::optional< SWD >,
                  std::optional< SUBSH >, std::optional< SPHEL >,
                  std::optional< XPROB >, std::optional< ESZE >,
                  std::optional< EXCIT >, std::optional< ELAS >,
                  std::vector< EION >, std::optional< BREME >,
                  std::optional< BREML >, std::optional< SELAS > >(),
    python::arg( "z" ), python::arg( "header" ),
    python::arg( "za" ), python::arg( "awr" ),
    python::arg( "eszg" ), python::arg( "jinc" ),
    python::arg( "jcoh" ), python::arg( "lhnm" ),
    python::arg( "jflo" ) = std::nullopt,
    python::arg( "eps" ) = std::nullopt,
    python::arg( "swd" ) = std::nullopt,
    python::arg( "subsh" ) = std::nullopt,
    python::arg( "sphel" ) = std::nullopt,
    python::arg( "xprob" ) = std::nullopt,
    python::arg( "esze" ) = std::nullopt,
    python::arg( "excit" ) = std::nullopt,
    python::arg( "elas" ) = std::nullopt,
    python::arg( "eion" ) = std::vector< EION >{},
    python::arg( "breme" ) = std::nullopt,
    python::arg( "breml" ) = std::nullopt,
    python::arg( "selas" ) = std::nullopt,
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    z         the Z number of the target\n"
    "    header    the header for the table\n"
    "    za        the list of ZA values\n"
    "    awr       the list of atomic mass values\n"
    "    eszg      the principal cross section block\n"
    "    jinc      the incoherent scattering function block\n"
    "    jcoh      the coherent form factor block\n"
    "    lhnm      the heating numbers block\n"
    "    jflo      the fluorescence data block\n"
    "    eps       the electron shell block\n"
    "    swd       the compton profile block\n"
    "    subsh     the electron subshell data block\n"
    "    sphel     the photoelectric cross section block\n"
    "    xprob     the atomic relaxation data block\n"
    "    esze      the electron cross section block\n"
    "    excit     the excitation energy loss data block\n"
    "    elas      the electron elastic angular distribution block\n"
    "    eion      the electronionisation data block\n"
    "    breme     the photon energy distributions from Bremsstrahlung\n"
    "    breml     the electron average energy after Bremsstrahlung\n"
    "    selas     the additional electron elastic cross section block"
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

    "S",
    &Table::S,
    "The isomeric state of the target"
  )
  .def_property_readonly(

    "isomeric_state",
    &Table::isomericState,
    "The isomeric state of the target"
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

    "NFLO",
    &Table::NFLO,
    "The number of fluorescence edges"
  )
  .def_property_readonly(

    "number_fluorescence_edges",
    &Table::numberFluorescenceEdges,
    "The number of fluorescence edges"
  )
  .def_property_readonly(

    "NSH",
    &Table::NSH,
    "The number of electron shells (for Compton Doppler broadening)"
  )
  .def_property_readonly(

    "number_electron_shells",
    &Table::numberElectronShells,
    "The number of electron shells (for Compton Doppler broadening)"
  )
  .def_property_readonly(

    "NEPR",
    &Table::NEPR,
    "The EPR data format flag (0 for the old mcplib format, 1 for EPR data from\n"
    "2012 and 3 for EPR data from 2014 and above)"
  )
  .def_property_readonly(

    "electron_photon_relaxation_format",
    &Table::electronPhotonRelaxationFormat,
    "The EPR data format flag (0 for the old mcplib format, 1 for EPR data from\n"
    "2012 and 3 for EPR data from 2014 and above)"
  )
  .def_property_readonly(

    "NSSH",
    &Table::NSSH,
    "The number of subshells for photoelectric and electron impact ionization"
  )
  .def_property_readonly(

    "number_electron_subshells",
    &Table::numberElectronSubshells,
    "The number of subshells for photoelectric and electron impact ionization"
  )
  .def_property_readonly(

    "NE",
    &Table::NE,
    "The number of electron energy points"
  )
  .def_property_readonly(

    "number_electron_energy_points",
    &Table::numberElectronEnergyPoints,
    "The number of electron energy points"
  )
  .def_property_readonly(

    "NXL",
    &Table::NXL,
    "The number of electron excitation energy points"
  )
  .def_property_readonly(

    "number_electron_excitation_energy_points",
    &Table::numberElectronExcitationEnergyPoints,
    "The number of electron excitation energy points"
  )
  .def_property_readonly(

    "NA",
    &Table::NA,
    "The number of energy points with electron elastic angular distributions"
  )
  .def_property_readonly(

    "number_electron_elastic_energy_points",
    &Table::numberElectronElasticEnergyPoints,
    "The number of energy points with electron elastic angular distributions"
  )
  .def_property_readonly(

    "NB",
    &Table::NB,
    "The number of energy points with Bremsstrahlung photon energy distributions"
  )
  .def_property_readonly(

    "number_electron_bremsstrahlung_energy_points",
    &Table::numberElectronBremsstrahlungEnergyPoints,
    "The number of energy points with Bremsstrahlung photon energy distributions"
  )
  .def_property_readonly(

    "NBL",
    &Table::NBL,
    "The number of electron Bremsstrahlung energy points"
  )
  .def_property_readonly(

    "number_electron_bremsstrahlung_energy_points",
    &Table::numberElectronBremsstrahlungEnergyPoints,
    "The number of electron Bremsstrahlung energy points"
  )
  .def_property_readonly(

    "ESZG",
    &Table::ESZG,
    "The principal cross section block"
  )
  .def_property_readonly(

    "principal_cross_section_block",
    &Table::principalCrossSectionBlock,
    "The principal cross section block"
  )
  .def_property_readonly(

    "JINC",
    &Table::JINC,
    "The incoherent scattering function block"
  )
  .def_property_readonly(

    "incoherent_scattering_function_block",
    &Table::incoherentScatteringFunctionBlock,
    "The incoherent scattering function block"
  )
  .def_property_readonly(

    "JCOH",
    &Table::JCOH,
    "The coherent form factor block"
  )
  .def_property_readonly(

    "coherent_form_factor_block",
    &Table::coherentFormFactorBlock,
    "The coherent form factor block"
  )
  .def_property_readonly(

    "JFLO",
    &Table::JFLO,
    "The fluorescence data block"
  )
  .def_property_readonly(

    "fluorescence_data_block",
    &Table::fluorescenceDataBlock,
    "The fluorescence data block"
  )
  .def_property_readonly(

    "EPS",
    &Table::EPS,
    "The electron shell block"
  )
  .def_property_readonly(

    "heating_numbers_block",
    &Table::electronShellBlock,
    "The electron shell block"
  )
  .def_property_readonly(

    "LHNM",
    &Table::LHNM,
    "The heating numbers block"
  )
  .def_property_readonly(

    "heating_numbers_block",
    &Table::heatingNumbersBlock,
    "The heating numbers block"
  )
  .def_property_readonly(

    "EPS",
    &Table::EPS,
    "The electron shell block"
  )
  .def_property_readonly(

    "electron_shell_block",
    &Table::electronShellBlock,
    "The electron shell block"
  )
  .def_property_readonly(

    "SWD",
    &Table::SWD,
    "The compton profile block"
  )
  .def_property_readonly(

    "compton_profile_block",
    &Table::comptonProfileBlock,
    "The electron shell block"
  )
  .def_property_readonly(

    "SUBSH",
    &Table::SUBSH,
    "The electron subshell data block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "electron_subshell_block",
    &Table::electronSubshellBlock,
    "The electron subshell data block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "SPHEL",
    &Table::SPHEL,
    "The photolectric cross section block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "photoelectric_cross_section_block",
    &Table::photoelectricCrossSectionBlock,
    "The photolectric cross section block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "XPROB",
    &Table::XPROB,
    "The subshell transition data block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "subshell_transition_data_block",
    &Table::subshellTransitionDataBlock,
    "The subshell transition data block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "ESZE",
    &Table::ESZE,
    "The electron cross section block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "electron_cross_section_block",
    &Table::electronCrossSectionBlock,
    "The electron cross section block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "EXCIT",
    &Table::EXCIT,
    "The electron excitation energy loss block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "electron_excitation_energy_loss_block",
    &Table::electronExcitationEnergyLossBlock,
    "The electron excitation energy loss block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "ELAS",
    &Table::ELAS,
    "The electron elastic angular distribution block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "electron_elastic_angular_distribution_block",
    &Table::electronElasticAngularDistributionBlock,
    "The electron elastic angular distribution block for eprdata (NEPR > 0)"
  )
  .def(

    "EION",
    &Table::EION,
    python::arg( "index" ),
    "Return the knock-on electron energy distribution block for a subshell index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "electroionisation_energy_distribution_block",
    &Table::electroionisationEnergyDistributionBlock,
    python::arg( "index" ),
    "Return the knock-on electron energy distribution block for a subshell index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "BREME",
    &Table::BREME,
    "The Bremsstrahlung energy distribution block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "bremsstrahlung_energy_distribution_block",
    &Table::bremsstrahlungEnergyDistributionBlock,
    "The Bremsstrahlung energy distribution block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "BREML",
    &Table::BREML,
    "The electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "electron_energy_after_bremsstrahlung_block",
    &Table::electronEnergyAfterBremsstrahlungBlock,
    "The electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)"
  )
  .def_property_readonly(

    "SELAS",
    &Table::SELAS,
    "The additional elastic cross section block for eprdata (NEPR = 3)"
  )
  .def_property_readonly(

    "electron_elastic_cross_section_block",
    &Table::electronElasticCrossSectionBlock,
    "The additional elastic cross section block for eprdata (NEPR = 3)"
  );

  // add standard block definitions
  addStandardTableDefinitions< Table >( table );
}
