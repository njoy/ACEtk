// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/Table.hpp"
#include "ACEtk/fromFile.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTable( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ACEtk::Table;
  //using Header = njoy::ACEtk::Table::Header;
  //using Data = njoy::ACEtk::Table::Data;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Table",
    "A generic ACE table\n\n"
    "A Table represents the generic ACE table, which can be of any type\n"
    "(e.g. continuous energy, thermal scattering, etc.). It contains a header\n"
    "and the actual data of the table (the data being the IZAW, NXS, JXS and XSS\n"
    "arrays)."
  );

  // wrap the component
  component
//  .def(
//
//    python::init< Header&&, Data&& >(),
//    python::arg( "header" ), python::arg( "data" ),
//    "Initialise the component\n\n"
//    "Arguments:\n"
//    "    self     the table\n"
//    "    header   the header information\n"
//    "    data     the ACE data"
//  )
  .def_property_readonly(

    "header",
    python::overload_cast<>( &Component::header, python::const_ ),
    "The header information"
  )
  .def_property_readonly(

    "data",
    python::overload_cast<>( &Component::data, python::const_ ),
    "The data arrays"
  )
  .def_static(

    "from_file",
    [] ( const std::string& filename ) -> Component {

      return njoy::ACEtk::fromFile( filename );
    },
    "Read an ACE table from a file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "table\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  )
  .def(

    "to_file",
    [] ( const Component& self, const std::string& filename ) {

      std::ofstream out( filename );
      self.print( out );
      out.close();
    },
    "Write the ACE table to a file\n\n"
    "Arguments:\n"
    "    self        the table\n"
    "    filename    the file name and path"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string ) -> Component {

      njoy::ACEtk::State< decltype(string.begin()) > state{ 1, string.begin(), string.end() };
      return Component( state );
    },
    python::arg( "string" ),
    "Read the ACE table from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "table\n\n"
    "Arguments:\n"
    "    string    the string representing the ACE table"
  )
  .def(

    "to_string",
    [] ( const Component& self ) {

      std::ostringstream out;
      self.print( out );
      return out.str();
    },
    "Return the string representation of the ACE table"
  );
}
