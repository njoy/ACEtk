// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/ThermalScatteringTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapThermalScatteringTable( python::module& module, python::module& ) {

  // type aliases
  using Header = njoy::ACEtk::Table::Header;
  using Table = njoy::ACEtk::ThermalScatteringTable;
  using ITIE = njoy::ACEtk::thermal::ITIE;
  using ITXE = njoy::ACEtk::thermal::ITXE;
  using ITCE = njoy::ACEtk::thermal::ITCE;
  using ITCA = njoy::ACEtk::thermal::ITCA;
  using ITCEI = njoy::ACEtk::thermal::ITCEI;
  using ITCAI = njoy::ACEtk::thermal::ITCAI;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "ThermalScatteringTable",
    "A thermal scattering ACE table\n\n"
    "The ThermalScatteringTable class represents the ACE table for thermal\n"
    "scattering data."
  );

  // wrap the table
  table
  .def(

    python::init< Header, std::vector< unsigned int >,
                  ITIE, ITXE,
                  std::optional< ITCE >, std::optional< ITCA >,
                  std::optional< ITCEI >, std::optional< ITCAI > >(),
    python::arg( "header" ), python::arg( "za" ),
    python::arg( "itie" ), python::arg( "itxe" ),
    python::arg( "itce" ) = std::nullopt, python::arg( "itca" ) = std::nullopt,
    python::arg( "itcei" ) = std::nullopt, python::arg( "itcai" ) = std::nullopt,
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    header    the header for the table\n"
    "    za        the list of ZA values\n"
    "    itie      the inelastic thermal scattering cross section block\n"
    "    itxe      the inelastic thermal scattering angular distribution block\n"
    "    itce      the coherent elastic thermal scattering cross section block\n"
    "    itca      the coherent elastic thermal scattering angular distribution block\n"
    "    itcei     the incoherent elastic thermal scattering cross section block\n"
    "    itcai     the incoherent elastic thermal scattering angular distribution block"
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

    "IDPNI",
    &Table::IDPNI,
    "The inelastic scattering mode"
  )
  .def_property_readonly(

    "inelastic_scattering_mode",
    &Table::inelasticScatteringMode,
    "The inelastic scattering mode"
  )
  .def_property_readonly(

    "NIL",
    &Table::NIL,
    "The inelastic dimensioning parameter\n\n"
    "For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,\n"
    "for IFENG = 2 this will be equal to NC + 1\n"
  )
  .def_property_readonly(

    "inelastic_dimensioning_parameter",
    &Table::inelasticDimensioningParameter,
    "The inelastic dimensioning parameter"
    "For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,\n"
    "for IFENG = 2 this will be equal to NC + 1\n"
  )
  .def_property_readonly(

    "NIEB",
    &Table::NIEB,
    "The number of inelastic outgoing energies"
  )
  .def_property_readonly(

    "number_inelastic_outgoing_energies",
    &Table::numberInelasticOutgoingEnergies,
    "The number of inelastic outgoing energies"
  )
  .def_property_readonly(

    "IDPNC",
    &Table::IDPNC,
    "The elastic scattering mode"
  )
  .def_property_readonly(

    "elastic_scattering_mode",
    &Table::elasticScatteringMode,
    "The elastic scattering mode"
  )
  .def_property_readonly(

    "NCL",
    &Table::NCL,
    "The first elastic dimensioning parameter\n\n"
    "The elastic dimensioning parameter is equal to NC - 1"
  )
  .def_property_readonly(

    "first_elastic_dimensioning_parameter",
    &Table::firstElasticDimensioningParameter,
    "The first elastic dimensioning parameter\n\n"
    "The elastic dimensioning parameter is equal to NC - 1"
  )
  .def_property_readonly(

    "NCLI",
    &Table::NCLI,
    "The second elastic dimensioning parameter\n\n"
    "The elastic dimensioning parameter is equal to NC - 1"
  )
  .def_property_readonly(

    "second_elastic_dimensioning_parameter",
    &Table::secondElasticDimensioningParameter,
    "The second elastic dimensioning parameter\n\n"
    "The elastic dimensioning parameter is equal to NC - 1"
  )
  .def_property_readonly(

    "IFENG",
    &Table::IFENG,
    "The secondary energy mode"
  )
  .def_property_readonly(

    "secondary_energy_mode",
    &Table::secondaryEnergyMode,
    "The secondary energy mode"
  )
  .def_property_readonly(

    "ITIE",
    &Table::ITIE,
    "The inelastic thermal scattering cross section block"
  )
  .def_property_readonly(

    "inelastic_cross_section_block",
    &Table::inelasticCrossSectionBlock,
    "The inelastic thermal scattering cross section block"
  )
  .def_property_readonly(

    "ITXE",
    &Table::ITXE,
    "The inelastic thermal scattering angular distribution block"
  )
  .def_property_readonly(

    "inelastic_angular_distribution_block",
    &Table::inelasticAngularDistributionBlock,
    "The inelastic thermal scattering angular distribution block"
  )
  .def_property_readonly(

    "ITCE",
    &Table::ITCE,
    "The coherent elastic thermal scattering cross section block"
  )
  .def_property_readonly(

    "coherent_elastic_cross_section_block",
    &Table::coherentElasticCrossSectionBlock,
    "The coherent elastic thermal scattering cross section block"
  )
  .def_property_readonly(

    "ITCA",
    &Table::ITCA,
    "The coherent elastic thermal scattering angular distribution block"
  )
  .def_property_readonly(

    "coherent_elastic_angular_distribution_block",
    &Table::coherentElasticAngularDistributionBlock,
    "The incoherent elastic thermal scattering angular distribution block"
  )
  .def_property_readonly(

    "ITCEI",
    &Table::ITCEI,
    "The incoherent elastic thermal scattering cross section block"
  )
  .def_property_readonly(

    "incoherent_elastic_cross_section_block",
    &Table::incoherentElasticCrossSectionBlock,
    "The incoherent elastic thermal scattering cross section block"
  )
  .def_property_readonly(

    "ITCAI",
    &Table::ITCAI,
    "The incoherent elastic thermal scattering angular distribution block"
  )
  .def_property_readonly(

    "incoherent_elastic_angular_distribution_block",
    &Table::incoherentElasticAngularDistributionBlock,
    "The incoherent elastic thermal scattering angular distribution block"
  );

  // add standard block definitions
  addStandardTableDefinitions< Table >( table );
}
