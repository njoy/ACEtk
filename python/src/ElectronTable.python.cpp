// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/ElectronTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapElectronTable( python::module& module, python::module& ) {
  
  // type aliases
  using HeaderVariant = njoy::ACEtk::Table::HeaderVariant;
  using Table = njoy::ACEtk::ElectronTable;
  using EKT = njoy::ACEtk::electron::EKT;
  using RAD = njoy::ACEtk::electron::RAD;
  using MOT = njoy::ACEtk::electron::MOT;
  using RLY = njoy::ACEtk::electron::RLY;
  using XSB = njoy::ACEtk::electron::XSB;
  using CRB = njoy::ACEtk::electron::CRB;
  using HFB = njoy::ACEtk::electron::HFB;
  using RKT = njoy::ACEtk::electron::RKT;
  using RKA = njoy::ACEtk::electron::RKA;
  using OSC = njoy::ACEtk::electron::OSC;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "ElectronTable",
    "An electron ACE table\n\n"
    "The ElectronTable class represents the ACE table for electron data."
  );

  // wrap the table
  table
  .def(
  
    python::init< unsigned int, HeaderVariant,
                  std::vector< unsigned int >, std::vector< double >,
                  EKT, RAD, MOT, RLY,
                  std::optional< XSB >, std::optional< CRB >,
                  std::optional< HFB >, std::optional< RKT >,
                  std::optional< RKA >, std::optional< OSC > >(),
    python::arg( "z" ), python::arg( "header" ),
    python::arg( "za" ), python::arg( "awr" ),
    python::arg( "ekt" ), python::arg( "rad" ),
    python::arg( "mot" ), python::arg( "rly" ),
    python::arg( "xsb" ) = std::nullopt,
    python::arg( "crb" ) = std::nullopt,
    python::arg( "hfb" ) = std::nullopt,
    python::arg( "rkt" ) = std::nullopt,
    python::arg( "rka" ) = std::nullopt,
    python::arg( "osc" ) = std::nullopt,
    "Initialize the table\n\n"
    "Arguments:\n"
    "    z         the Z number of the target\n"
    "    header    the header for the table\n"
    "    za        the list of ZA values\n"
    "    awr       the list of atomic mass values\n"
    "    ekt       the transition energy block\n"
    "    rad       the radiation stopping power block\n"
    "    mot       the Mott scattering correction block\n"
    "    rly       the Riley cross section block\n"
    "    xsb       the brmsstrahlung production block (NEL == 3)\n"
    "    crb       the bremsstrahlung correction factor block (NEL != 3)\n"
    "    hfb       the bremsstrahlung high-frequency block (NEL != 3)\n"
    "    rkt       the bremsstrahlung energy spectrum block (NEL == 3)\n"
    "    rka       the bremsstrahlung angular spectrum block (NEL == 3)\n"
    "    osc       the oscillator block (NEL == 3)"
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
  
    "NEL",
    &Table::NEL,
    "The EL data format flag (0 or 3)"
  )
  .def_property_readonly(
  
    "electron_data_format",
    &Table::electronDataFormat,
    "The EL data format flag (0 or 3)"
  )
  .def_property_readonly(
  
    "NRAD",
    &Table::NRAD,
    "The number of radiation stopping power points"
  )
  .def_property_readonly(
  
    "number_radiation_stopping_points",
    &Table::numberRadiationStoppingPoints,
    "The number of radiation stopping power points"
  )
  .def_property_readonly(
  
    "NMOT",
    &Table::NMOT,
    "The number of Mott scattering correction points"
  )
  .def_property_readonly(
  
    "number_mott_correction_points",
    &Table::numberMottCorrectionPoints,
    "The number of Mott scattering correction points"
  )
  .def_property_readonly(
  
    "NEB",
    &Table::NEB,
    "The number of electron energy points for bremsstrahlung production\n"
    "(NEL == 3)"
  )
  .def_property_readonly(
  
    "number_electron_bremsstrahlung_energy_points",
    &Table::numberElectronBremsstrahlungEnergyPoints,
    "The number of electron energy points for bremsstrahlung production\n"
    "(NEL == 3)"
  )
  .def_property_readonly(
  
    "NPB",
    &Table::NPB,
    "The number of photon ratio points for bremsstrahlung production\n"
    "(NEL == 3)"
  )
  .def_property_readonly(
  
    "number_photon_bremsstrahlung_ratio_points",
    &Table::numberPhotonBremsstrahlungRatioPoints,
    "The number of photon ratio points for bremsstrahlung production\n"
    "(NEL == 3)"
  )
  .def_property_readonly(
  
    "NCRB",
    &Table::NCRB,
    "The number of bremsstrahlung correction factor points (NEL != 3)"
  )
  .def_property_readonly(
  
    "number_bremsstrahlung_correction_points",
    &Table::numberBremsstrahlungCorrectionPoints,
    "The number of bremsstrahlung correction factor points (NEL != 3)"
  )
  .def_property_readonly(
  
    "NHFB",
    &Table::NHFB,
    "The number of bremsstrahlung high-frequency limit points (NEL != 3)"
  )
  .def_property_readonly(
  
    "number_bremsstrahlung_high_frequency_points",
    &Table::numberBremsstrahlungHighFrequencyPoints,
    "The number of bremsstrahlung high-frequency limit points (NEL != 3)"
  )
  .def_property_readonly(
  
    "NRKT",
    &Table::NRKT,
    "The number of bremsstrahlung energy spectrum points (NEL == 3)"
  )
  .def_property_readonly(
  
    "number_bremsstrahlung_energy_spectrum_points",
    &Table::numberBremsstrahlungEnergySpectrumPoints,
    "The number of bremsstrahlung energy spectrum points (NEL == 3)"
  )
  .def_property_readonly(
  
    "NRKA",
    &Table::NRKA,
    "The number of bremsstrahlung angular spectrum points (NEL == 3)"
  )
  .def_property_readonly(
  
    "number_bremsstrahlung_angular_spectrum_points",
    &Table::numberBremsstrahlungAngularSpectrumPoints,
    "The number of bremsstrahlung angular spectrum points (NEL == 3)"
  )
  .def_property_readonly(
  
    "NOSC",
    &Table::NOSC,
    "The number of oscillator points (NEL == 3)"
  )
  .def_property_readonly(
  
    "number_oscillator_points",
    &Table::numberOscillatorPoints,
    "The number of oscillator points (NEL == 3)"
  )
  .def_property_readonly(
  
    "EKT",
    &Table::EKT,
    "The transition energy block"
  )
  .def_property_readonly(
  
    "transition_energy_block",
    &Table::transitionEnergyBlock,
    "The transition energy block"
  )
  .def_property_readonly(
  
    "RAD",
    &Table::RAD,
    "The radiation stopping power block"
  )
  .def_property_readonly(
  
    "radiation_stopping_power_block",
    &Table::radiationStoppingPowerBlock,
    "The radiation stopping power block"
  )
  .def_property_readonly(
  
    "MOT",
    &Table::MOT,
    "The Mott scattering correction block"
  )
  .def_property_readonly(
  
    "mott_scattering_correction_block",
    &Table::mottScatteringCorrectionBlock,
    "The Mott scattering correction block"
  )
  .def_property_readonly(
  
    "RLY",
    &Table::RLY,
    "The Riley cross section block"
  )
  .def_property_readonly(
  
    "riley_cross_section_block",
    &Table::rileyCrossSectionBlock,
    "The Riley cross section block"
  )
  .def_property_readonly(
  
    "XSB",
    &Table::XSB,
    "The bremsstrahlung production block (NEL == 3)"
  )
  .def_property_readonly(
  
    "bremsstrahlung_production_block",
    &Table::bremsstrahlungProductionBlock,
    "The bremsstrahlung production block (NEL == 3)"
  )
  .def_property_readonly(
  
    "CRB",
    &Table::CRB,
    "The bremsstrahlung correction factor block (NEL != 3)"
  )
  .def_property_readonly(
  
    "bremsstrahlung_correction_factor_block",
    &Table::bremsstrahlungCorrectionFactorBlock,
    "The bremsstrahlung correction factor block (NEL != 3)"
  )
  .def_property_readonly(
  
    "HFB",
    &Table::HFB,
    "The bremsstrahlung high-frequency block (NEL != 3)"
  )
  .def_property_readonly(
  
    "bremsstrahlung_high_frequency_block",
    &Table::bremsstrahlungHighFrequencyBlock,
    "The bremsstrahlung high-frequency block (NEL != 3)"
  )
  .def_property_readonly(
  
    "RKT",
    &Table::RKT,
    "The bremsstrahlung energy spectrum block (NEL == 3)"
  )
  .def_property_readonly(
  
    "bremsstrahlung_energy_spectrum_block",
    &Table::bremsstrahlungEnergySpectrumBlock,
    "The bremsstrahlung energy spectrum block (NEL == 3)"
  )
  .def_property_readonly(
  
    "RKA",
    &Table::RKA,
    "The bremsstrahlung angular spectrum block (NEL == 3)"
  )
  .def_property_readonly(
  
    "bremsstrahlung_angular_spectrum_block",
    &Table::bremsstrahlungAngularSpectrumBlock,
    "The bremsstrahlung angular spectrum block (NEL == 3)"
  )
  .def_property_readonly(
  
    "OSC",
    &Table::OSC,
    "The oscillator block (NEL == 3)"
  )
  .def_property_readonly(
  
    "oscillator_block",
    &Table::oscillatorBlock,
    "The oscillator block (NEL == 3)"
  );

  // add standard block definitions
  addStandardTableDefinitions< Table >( table );
}