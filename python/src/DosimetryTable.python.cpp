// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/DosimetryTable.hpp"
#include "ACEtk/fromFile.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapDosimetryTable( python::module& module, python::module& ) {

  // type aliases
  using Table = njoy::ACEtk::DosimetryTable;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "DosimetryTable",
    "A dosimetry ACE table\n\n"
    "The DosimetryTable class represents the ACE table for dosimetry data."
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

    "SIGD",
    &Table::SIGD,
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
