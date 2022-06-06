// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/PhotoAtomicTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapPhotoAtomicTable( python::module& module, python::module& ) {

  // type aliases
  using Header = njoy::ACEtk::Table::Header;
  using Table = njoy::ACEtk::PhotoAtomicTable;
  using ESZG = njoy::ACEtk::block::ESZG;
  using JINC = njoy::ACEtk::block::JINC;
  using JCOH = njoy::ACEtk::block::JCOH;
  using LHNM = njoy::ACEtk::block::LHNM;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "PhotoAtomicTable",
    "A thermal scattering ACE table\n\n"
    "The PhotoAtomicTable class represents the ACE table for photoatomic data."
  );

  // wrap the table
  table
  .def(

    python::init< Header, std::vector< unsigned int >, std::vector< double >,
                  ESZG, JINC, JCOH, LHNM >(),
    python::arg( "header" ), python::arg( "za" ), python::arg( "awr" ),
    python::arg( "eszg" ), python::arg( "jinc" ), python::arg( "jcoh" ),
    python::arg( "lhnm" ),
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    header    the header for the table\n"
    "    za        the list of ZA values\n"
    "    awr       the list of atomic mass values\n"
    "    eszg      the principal cross section block\n"
    "    jinc      the incoherent scattering function block\n"
    "    jcoh      the coherent form factor block\n"
    "    lhnm      the heating numbers block"
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
