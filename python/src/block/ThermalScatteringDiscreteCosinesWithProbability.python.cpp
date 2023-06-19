// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ThermalScatteringDiscreteCosinesWithProbability.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapThermalScatteringDiscreteCosinesWithProbability( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ThermalScatteringDiscreteCosinesWithProbability;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ThermalScatteringDiscreteCosinesWithProbability",
    "Discrete cosines for a single outgoing energy value used in thermal "
    "scattering secondary particle distributions\n\n"
    "The ThermalScatteringDiscreteCosinesWithProbability class contains an outgoing\n"
    "energy value, the corresponding pdf and cdf value and the associated\n"
    "discrete cosine values. It is used in the ITXE block (for inelastic thermal\n"
    "scattering data) when IFENG = 2. This is the current standard ACE format\n"
    "used in inelastic thermal scattering."
  );

  // wrap the block
  block
  .def(

    python::init< double, double, double, std::vector< double > >(),
    python::arg( "energy" ), python::arg( "pdf" ),
    python::arg( "cdf" ), python::arg( "cosines" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self       the block\n"
    "    energy     the outgoing energy value\n"
    "    pdf        the pdf value\n"
    "    cdf        the cdf value\n"
    "    cosines    the cosine values"
  )
  .def_property_readonly(

    "energy",
    &Block::energy,
    "The outgoing energy value"
  )
  .def_property_readonly(

    "pdf",
    &Block::pdf,
    "The pdf  value"
  )
  .def_property_readonly(

    "cdf",
    &Block::cdf,
    "The cdf value"
  )
  .def_property_readonly(

    "NC",
    &Block::NC,
    "The number of discrete cosines"
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
