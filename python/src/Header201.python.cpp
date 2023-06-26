// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/Table.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapHeader201( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ACEtk::Table::Header201;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Header201",
    "The header in an ACE table"
  );

  // wrap the component
  component
  .def(

    python::init< const std::string&, const std::string&,
                  double, double, const std::string&,
                  const std::vector< std::string >& >(),
    python::arg( "szaid" ), python::arg( "source" ), python::arg( "awr" ),
    python::arg( "temperature" ), python::arg( "date" ),
    python::arg( "comments" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the header\n"
    "    szaid         the szaid (max 10 characters)\n"
    "    source        the source of the file\n"
    "    awr           the atomic weight ratio (to the neutron mass)\n"
    "    temperature   the temperature in MeV\n"
    "    date          the date (max 10 characters)\n"
    "    comments      the comments"
  )
  .def_property_readonly(

    "VERS",
    &Component::VERS,
    "The header version"
  )
  .def_property_readonly(

    "version",
    &Component::version,
    "The header version"
  )
  .def_property_readonly(

    "zaid",
    &Component::ZAID,
    "The full ZAID or SZAID of the table"
  )
  .def_property_readonly(

    "AWR",
    &Component::AWR,
    "The atomic weight ratio (with respect to the neutron mass)"
  )
  .def_property_readonly(

    "atomic_weight_ratio",
    &Component::atomicWeightRatio,
    "The atomic weight ratio (with respect to the neutron mass)"
  )
  .def_property_readonly(

    "TEMP",
    &Component::TEMP,
    "The temperature of the table"
  )
  .def_property_readonly(

    "temperature",
    &Component::temperature,
    "The temperature of the table"
  )
  .def_property_readonly(

    "date",
    &Component::date,
    "The date"
  )
  .def_property_readonly(

    "comments",
    &Component::comments,
    "The comments"
  );
}
