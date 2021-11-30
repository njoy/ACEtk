// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/EquiprobableAngularBins.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapEquiprobableAngularBins( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::EquiprobableAngularBins;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "EquiprobableAngularBins",
    "Convenience interface for equiprobable cosine bin data from the AND block"
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

} // block namespace
