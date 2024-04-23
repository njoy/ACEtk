// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/photoatomic/HeatingNumbersBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace photoatomic {

void wrapHeatingNumbersBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::photoatomic::HeatingNumbersBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "HeatingNumbersBlock",
    "The photoatomic LHNM block with the heating numbers\n\n"
    "The HeatingNumbersBlock class contains the heating numbers. The size of the\n"
    "array is stored in NXS(3) and the corresponding energy points can be found\n"
    "in the ESZG block."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "heating" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self       the block\n"
    "    heating    the heating numbers"
  )
  .def_property_readonly(

    "NES",
    &Block::NES,
    "The number of energy points"
  )
  .def_property_readonly(

    "number_energy_points",
    &Block::numberEnergyPoints,
    "The number of energy points"
  )
  .def_property_readonly(

    "heating",
    [] ( const Block& self ) -> DoubleRange
       { return self.heating(); },
    "The heating number"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // photoatomic namespace
