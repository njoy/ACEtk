// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/photoatomic/HeatingNumbersBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotoatomicHeatingNumbersBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotoatomicHeatingNumbersBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotoatomicHeatingNumbersBlock",
    "The photoatomic LHNM block with the heating numbers\n\n"
    "The PhotoatomicHeatingNumbersBlock class contains the heating numbers.\n"
    "The size of the array is stored in NXS(3) and the corresponding energy\n"
    "points can be found in the ESZG block."
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

} // block namespace
