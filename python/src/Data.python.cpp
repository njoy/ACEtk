// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/Table.hpp"

// namespace aliases
namespace python = pybind11;

void wrapData( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ACEtk::Table::Data;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Data",
    "The data in an ACE table\n\n"
    "The data in an ACE table consists of the following arrays:\n"
    "  - the IZAW array which contains 16 integer, double pairs\n"
    "  - the NXS array which contains information needed to properly interpret\n"
    "    the XSS array\n"
    "  - the JXS array which contains 32 locators to specific blocks in the\n"
    "    XSS array (the meaning of the JXS locators depend on the type of the\n"
    "    ACE table)\n"
    "  - the XSS array which contains the actual data"
  );

  // wrap the component
  component
  .def(

    python::init< std::array< int32_t, 16 >&&, std::array< double, 16 >&&,
                  std::array< int64_t, 16 >&&, std::array< int64_t, 32 >&&,
                  std::vector< double >&& >(),
    python::arg( "iz" ), python::arg( "aw" ), python::arg( "nxs" ),
    python::arg( "jxs" ), python::arg( "xss" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self    the data arrays\n"
    "    iz      the IZ array\n"
    "    aw      the AW array\n"
    "    nxs     the NXS array\n"
    "    jxs     the JXS array\n"
    "    xss     the XSS array"
  )
  .def_property_readonly(

    "iz_array",
    python::overload_cast<>( &Component::IZ, python::const_ ),
    "The iz array"
  )
  .def_property_readonly(

    "aw_array",
    python::overload_cast<>( &Component::AW, python::const_ ),
    "The aw array"
  )
  .def_property_readonly(

    "nxs_array",
    python::overload_cast<>( &Component::NXS, python::const_ ),
    "The nxs array"
  )
  .def_property_readonly(

    "jxs_array",
    python::overload_cast<>( &Component::JXS, python::const_ ),
    "The jxs array"
  )
  .def_property_readonly(

    "xss_array",
    python::overload_cast<>( &Component::XSS, python::const_ ),
    "The xss array"
  )
  .def(

    "iz",
    python::overload_cast< std::size_t >( &Component::IZ, python::const_ ),
    python::arg( "index" ),
    "Return a value from the IZ array\n\n"
    "Arguments:\n"
    "    self     the data arrays\n"
    "    index    the index (one-based)"
  )
  .def(

    "aw",
    python::overload_cast< std::size_t >( &Component::AW, python::const_ ),
    python::arg( "index" ),
    "Return a value from the AW array\n\n"
    "Arguments:\n"
    "    self     the data arrays\n"
    "    index    the index (one-based)"
  )
  .def(

    "nxs",
    python::overload_cast< std::size_t >( &Component::NXS, python::const_ ),
    python::arg( "index" ),
    "Return a value from the NXS array\n\n"
    "Arguments:\n"
    "    self     the data arrays\n"
    "    index    the index (one-based)"
  )
  .def(

    "jxs",
    python::overload_cast< std::size_t >( &Component::JXS, python::const_ ),
    python::arg( "index" ),
    "Return a value from the JXS array\n\n"
    "Arguments:\n"
    "    self     the data arrays\n"
    "    index    the index (one-based)"
  )
  .def(

    "xss",
    python::overload_cast< std::size_t >( &Component::XSS, python::const_ ),
    python::arg( "index" ),
    "Return a value from the XSS array\n\n"
    "Arguments:\n"
    "    self     the data arrays\n"
    "    index    the index (one-based)"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string ) -> Component {

      njoy::ACEtk::State< decltype(string.begin()) > state{ 1, string.begin(), string.end() };
      return Component( state );
    },
    python::arg( "string" ),
    "Read the ACE data arrays from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "data arrays\n\n"
    "Arguments:\n"
    "    string    the string representing the ACE data arrays"
  )
  .def(

    "to_string",
    [] ( const Component& self ) {

      std::ostringstream out;
      self.print( out );
      return out.str();
    },
    "Return the string representation of the ACE data arrays"
  );
}
