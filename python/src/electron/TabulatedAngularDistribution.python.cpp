// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ElectronTabulatedAngularDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapElectronTabulatedAngularDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ElectronTabulatedAngularDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ElectronTabulatedAngularDistribution",
    "Tabulated electron angular distribution data for a single incident energy\n\n"
    "The ElectronTabulatedAngularDistribution class contains the cumulative\n"
    "density function (CDF) as a function of cosine for the given incident\n"
    "energy. It is used in the ELAS block."
  );

  // wrap the block
  block
  .def(

    python::init< double, std::vector< double >, std::vector< double > >(),
    python::arg( "energy" ),  python::arg( "cosines" ), python::arg( "cdf" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self            the block\n"
    "    energy          the associated incident energy value\n"
    "    cosines         the cosine values\n"
    "    cdf             the cdf values"
  )
  .def_property_readonly(

    "energy",
    &Block::energy,
    "The associated incident energy value"
  )
  .def_property_readonly(

    "number_cosines",
    &Block::numberCosines,
    "The number of cosine values"
  )
  .def_property_readonly(

    "cosines",
    [] ( const Block& self ) -> DoubleRange
       { return self.cosines(); },
    "The cosine values"
  )
  .def_property_readonly(

    "cdf",
    [] ( const Block& self ) -> DoubleRange
       { return self.cdf(); },
    "The cdf values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
