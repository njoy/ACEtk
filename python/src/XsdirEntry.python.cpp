// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/XsdirEntry.hpp"

// namespace aliases
namespace python = pybind11;

void wrapXsdirEntry( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ACEtk::XsdirEntry;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "XsdirEntry",
    "An entry in an xsdir file\n\n"
    "An xsdir entry consists of either 7, 10 or 11 values:\n"
    "  - the zaid\n"
    "  - the atomic mass ratio\n"
    "  - file name\n"
    "  - an access path (undefined path if \'0\')\n"
    "  - a file type (1 for ascii, 2 for binary)\n"
    "  - the starting address or line number\n"
    "  - the table length (number of words in the XSS array)\n"
    "  - the length of a record (0 for ascii files)\n"
    "  - the number of entries (0 for ascii files)\n"
    "  - the temperature in MeV\n"
    "  - ptable if the table has a probability table for the URR"
  );

  // wrap the component
  component
  .def(

    python::init< std::string, double, std::string,
                  unsigned int, unsigned int, unsigned int,
                  std::optional< std::string >,
                  std::optional< unsigned int >,
                  std::optional< unsigned int >,
                  std::optional< double >,
                  bool >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "filename" ),
    python::arg( "filetype" ), python::arg( "address" ),
    python::arg( "length" ), python::arg( "access" ) = std::nullopt,
    python::arg( "recordlength" ) = std::nullopt,
    python::arg( "entries" ) = std::nullopt,
    python::arg( "temperature" ) = std::nullopt,
    python::arg( "ptable" ) = false,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the xsdir entry\n"
    "    zaid            the zaid\n"
    "    awr             the atomic weight ratio (to the neutron mass)\n"
    "    filename        the file name\n"
    "    address         the starting address or line\n"
    "    length          the length of the file\n"
    "    access          the access path for the file (optional)\n"
    "    recordlength    the length of a record (optional)\n"
    "    entries         the number of entries per record (optional)\n"
    "    temperature     the temperature of the file (optional)\n"
    "    ptable          flag to indicate if a probability table is present"
  )
  .def_property_readonly(

    "zaid",
    &Component::ZAID,
    "The ZAID of the table"
  )
  .def_property_readonly(

    "awr",
    &Component::AWR,
    "The atomic weight ratio (with respect to the neutron mass)"
  )
  .def_property_readonly(

    "atomic_weight_ratio",
    &Component::atomicWeightRatio,
    "The atomic weight ratio (with respect to the neutron mass)"
  )
  .def_property_readonly(

    "file_name",
    &Component::fileName,
    "The file name and path"
  )
  .def_property_readonly(

    "access_route",
    &Component::accessRoute,
    "The access route"
  )
  .def_property_readonly(

    "file_type",
    &Component::fileType,
    "The file type"
  )
  .def_property_readonly(

    "address",
    &Component::address,
    "The table address or starting line"
  )
  .def_property_readonly(

    "table_length",
    &Component::tableLength,
    "The table length"
  )
  .def_property_readonly(

    "record_length",
    &Component::recordLength,
    "The record length (used for binary files only)"
  )
  .def_property_readonly(

    "entries_per_record",
    &Component::entriesPerRecord,
    "The number of entries per record (used for binary files only)"
  )
  .def_property_readonly(

    "temperature",
    &Component::temperature,
    "The temperature of the table (if it is defined)"
  )
  .def_property_readonly(

    "ptable",
    &Component::ptable,
    "The flag indicating whether or not a probability table is present"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string ) -> Component {

      std::istringstream in( string );
      return Component( in );
    },
    python::arg( "string" ),
    "Read the xsdir entry from a string\n\n"
    "An exception is raised if something goes wrong while reading the entry\n\n"
    "Arguments:\n"
    "    string    the string representing the xsdir entry"
  )
  .def(

    "to_string",
    [] ( const Component& self ) {

      std::ostringstream out;
      self.print( out );
      return out.str();
    },
    "Return the string representation of the xsdir entry"
  );
}
