// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ThermalScatteringDiscreteCosines.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapThermalScatteringDiscreteCosines( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ThermalScatteringDiscreteCosines;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ThermalScatteringDiscreteCosines",
    "Discrete cosines for a single outgoing energy value used in thermal "
    "scattering secondary particle distributions\n\n"
    "The ThermalScatteringDiscreteCosines class contains an outgoing\n"
    "energy value and the associated discrete cosine values. It is used in the\n"
    "ITXE block (for inelastic thermal scattering data) when IFENG = 0 or 1."
  );

  // wrap the block
  block
  .def(

    python::init< double, std::vector< double > >(),
    python::arg( "energy" ), python::arg( "cosines" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    energy      the outgoing energy value\n"
    "    cosines     the cosine values"
  )
  .def_property_readonly(

    "energy",
    &Block::energy,
    "The outgoing energy value"
  )
  .def_property_readonly(

    "number_discrete_cosines",
    &Block::numberDiscreteCosines,
    "The number of discrete cosines"
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
