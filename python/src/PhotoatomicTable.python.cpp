// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/PhotoatomicTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapPhotoatomicTable( python::module& module, python::module& ) {

  // type aliases
  using HeaderVariant = njoy::ACEtk::Table::HeaderVariant;
  using Table = njoy::ACEtk::PhotoatomicTable;
  using ESZG = njoy::ACEtk::block::ESZG;
  using JINC = njoy::ACEtk::block::JINC;
  using JCOH = njoy::ACEtk::block::JCOH;
  using JFLO = njoy::ACEtk::block::JFLO;
  using LHNM = njoy::ACEtk::block::LHNM;
  using EPS = njoy::ACEtk::block::EPS;
  using SWD = njoy::ACEtk::block::SWD;

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
                  std::optional< EPS >, std::optional< SWD > >(),
    python::arg( "z" ), python::arg( "header" ),
    python::arg( "za" ), python::arg( "awr" ),
    python::arg( "eszg" ), python::arg( "jinc" ),
    python::arg( "jcoh" ), python::arg( "lhnm" ),
    python::arg( "jflo" ) = std::nullopt,
    python::arg( "eps" ) = std::nullopt,
    python::arg( "swd" ) = std::nullopt,
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    header    the header for the table\n"
    "    za        the list of ZA values\n"
    "    awr       the list of atomic mass values\n"
    "    eszg      the principal cross section block\n"
    "    jinc      the incoherent scattering function block\n"
    "    jcoh      the coherent form factor block\n"
    "    lhnm      the heating numbers block\n"
    "    lhnm      the fluorescence data block\n"
    "    eps       the electron shell block\n"
    "    swd       the compton profile block"
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

    "Z",
    &Table::Z,
    "The atom number of the element"
  )
  .def_property_readonly(

    "atom_number",
    &Table::atomNumber,
    "The atom number of the element"
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

    "Z",
    &Table::Z,
    "The atom number of the element"
  )
  .def_property_readonly(

    "atom_number",
    &Table::atomNumber,
    "The atom number of the element"
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
    "The EPR data format flag (0 for old format and 1 for EPR data)"
  )
  .def_property_readonly(

    "electron_photon_relaxation_format",
    &Table::electronPhotonRelaxationFormat,
    "The EPR data format flag (0 for old format and 1 for EPR data)"
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

    "ESZ",
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
  );

  // add standard block definitions
  addStandardTableDefinitions< Table >( table );
}
