#ifndef NJOY_ACETK_PYTHON_DEFINITIONS
#define NJOY_ACETK_PYTHON_DEFINITIONS

// system includes
#include <complex>

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "views.hpp"

namespace python = pybind11;

/**
 *  @brief Add standard lock definitions
 *
 *  This adds the following standard properties:
 *    name, length, xss_array
 *
 *  @param[in] component   the block to which the definitions have to be added
 */
template < typename Block, typename PythonClass >
void addStandardBlockDefinitions( PythonClass& component ) {

  component
  .def_property_readonly(

    "name",
    [] ( const Block& self ) { return self.name(); },
    "The name of the block"
  )
  .def_property_readonly(

    "length",
    [] ( const Block& self ) { return self.length(); },
    "The length of the the xss array of the block"
  )
  .def_property_readonly(

    "xss_array",
    [] ( const Block& self ) -> DoubleRange
       { return self.XSS(); },
    "The xss array of the block"
  )
  .def(

    "xss",
    [] ( const Block& self, std::size_t index )
       { return self.XSS( index ); },
    python::arg( "index" ),
    "Return a value from the xss array of the block\n\n"
    "Arguments:\n"
    "    self     the data block\n"
    "    index    the index (one-based)"
  )
  .def(

    "xss",
    [] ( const Block& self, std::size_t index, std::size_t length ) -> DoubleRange
       { return self.XSS( index, length ); },
    python::arg( "index" ), python::arg( "length" ),
    "Return a subrange of a given length from the xss array of the block\n\n"
    "Arguments:\n"
    "    self      the data block\n"
    "    index     the index (one-based)\n"
    "    length    the length of the subrange"
  );
}

#endif
