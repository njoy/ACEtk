// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/EquiprobableAngularBins.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapEquiprobableAngularBins( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::EquiprobableAngularBins;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EquiprobableAngularBins",
    "Equiprobable angular bin data for a single incident energy value\n\n"
    "The EquiprobableAngularBins class contains the cosine values that make up\n"
    "the equiprobable bins (there are 33 values for defining 32 bins) for the\n"
    "associated incident energy. It is used in the AND block. This \n"
    "format is only used in old ACE data."
  );

  // wrap the block
  block
  .def(

    python::init< double, std::vector< double > >(),
    python::arg( "energy" ), python::arg( "cosines" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    energy      the associated energy value\n"
    "    cosines     the cosine values (33 values)"
  )
  .def_property_readonly(

    "energy",
    &Block::energy,
    "The associated energy value"
  )
  .def_property_readonly(

    "number_bins",
    [] ( const Block& self ) { return self.numberBins(); },
    "The number of equiprobable angular bins"
  )
  .def_property_readonly(

    "cosines",
    [] ( const Block& self ) -> DoubleRange
       { return self.cosines(); },
    "The cosine values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
