// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/PolynomialFissionMultiplicity.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapPolynomialFissionMultiplicity( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::PolynomialFissionMultiplicity;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PolynomialFissionMultiplicity",
    "Polynomial fission multiplicity\n\n"
    "The PolynomialFissionMultiplicity class contains the polynomial\n"
    "representation (LNU = 1) of the fission multiplicity. It is\n"
    "used in the NU block."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "coefficients" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self            the block\n"
    "    coefficients    the polynomial coefficients"
  )
  .def_property_readonly(

    "LNU",
    &Block::LNU,
    "The representation type (should always be 1)"
  )
  .def_property_readonly(

    "type",
    &Block::type,
    "The representation type (should always be 1)"
  )
  .def_property_readonly(

    "NC",
    &Block::NC,
    "The number of polynomial coefficients"
  )
  .def_property_readonly(

    "number_coefficients",
    &Block::numberCoefficients,
    "The number of polynomial coefficients"
  )
  .def_property_readonly(

    "C",
    [] ( const Block& self ) -> DoubleRange
       { return self.C(); },
    "The coefficients"
  )
  .def_property_readonly(

    "coefficients",
    [] ( const Block& self ) -> DoubleRange
       { return self.coefficients(); },
    "The coefficients"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
