// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/TabulatedAngularDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapTabulatedAngularDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::TabulatedAngularDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TabulatedAngularDistribution",
    "Tabulated angular distribution data for a single incident or outgoing energy\n"
    "The TabulatedAngularDistribution class contains the probability density\n"
    "function (PDF) and cumulative density function (CDF) as a function of\n"
    "cosine for the given energy. It is used in the AND block."
  );

  // wrap the block
  block
  .def(

    python::init< double, int, std::vector< double >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "energy" ), python::arg( "interpolation" ),
    python::arg( "cosines" ), python::arg( "pdf" ), python::arg( "cdf" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self            the block\n"
    "    energy          the associated energy value\n"
    "    interpolation   the interpolation type\n"
    "    cosines         the cosine values\n"
    "    pdf             the pdf values\n"
    "    cdf             the cdf values"
  )
  .def_property_readonly(

    "energy",
    &Block::energy,
    "The associated energy value"
  )
  .def_property_readonly(

    "interpolation",
    &Block::interpolation,
    "The interpolation flag"
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

    "pdf",
    [] ( const Block& self ) -> DoubleRange
       { return self.pdf(); },
    "The pdf values"
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

} // continuous namespace
