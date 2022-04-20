// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/ThermalScatteringTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapThermalScatteringTable( python::module& module, python::module& ) {

  // type aliases
  using Header = njoy::ACEtk::Table::Header;
  using Table = njoy::ACEtk::ThermalScatteringTable;

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
    "The inelastic dimensioning parameter"
  )
  .def_property_readonly(

    "inelastic_dimensioning_parameter",
    &Table::inelasticDimensioningParameter,
    "The inelastic dimensioning parameter"
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
    "The first elastic dimensioning parameter"
  )
  .def_property_readonly(

    "first_elastic_dimensioning_parameter",
    &Table::firstElasticDimensioningParameter,
    "The first elastic dimensioning parameter"
  )
  .def_property_readonly(

    "NCLI",
    &Table::NCLI,
    "The second elastic dimensioning parameter"
  )
  .def_property_readonly(

    "second_elastic_dimensioning_parameter",
    &Table::secondElasticDimensioningParameter,
    "The first elastic dimensioning parameter"
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

    "ITCEI",
    &Table::ITCEI,
    "The incoherent elastic thermal scattering cross section block"
  )
  .def_property_readonly(

    "incoherent_elastic_cross_section_block",
    &Table::coherentElasticCrossSectionBlock,
    "The incoherent elastic thermal scattering cross section block"
  );

  // add standard block definitions
  addStandardTableDefinitions< Table >( table );
}
