// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/TabulatedAngularDistributionWithProbability.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapTabulatedAngularDistributionWithProbability( python::module& module,
                                                      python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::TabulatedAngularDistributionWithProbability;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TabulatedAngularDistributionWithProbability",
    "Tabulated angular distribution data for a single incident or outgoing energy\n"
    "The TabulatedAngularDistributionWithProbability class contains the probability\n"
    "density function (PDF) and cumulative density function (CDF) as a function of\n"
    "cosine for the given energy and associated probability and cumulative probability.\n"
    "It is used in the OutgoingEnergyAngleDistributionData (ACE LAW 61) in the DLW block."
  );

  // wrap the block
  block
  .def(

    python::init< double, double, double, int,
                  std::vector< double >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "energy" ), python::arg( "probability" ),
    python::arg( "cumulative" ), python::arg( "interpolation" ),
    python::arg( "cosines" ), python::arg( "pdf" ), python::arg( "cdf" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self           the block\n"
    "    energy         the associated energy value\n"
    "    probability    the associated probability value\n"
    "    cumulative     the associated cumulative probability value\n"
    "    cosines        the cosine values\n"
    "    pdf            the pdf values\n"
    "    cdf            the cdf values"
  )
  .def_property_readonly(

    "energy",
    [] ( const Block& self ) { return self.energy(); },
    "The associated energy value"
  )
  .def_property_readonly(

    "probability",
    &Block::probability,
    "The associated probability value"
  )
  .def_property_readonly(

    "cumulative_probability",
    &Block::cumulativeProbability,
    "The associated cumulative probability value"
  )
  .def_property_readonly(

    "interpolation",
    [] ( const Block& self ) { return self.interpolation(); },
    "The interpolation flag"
  )
  .def_property_readonly(

    "number_cosines",
    [] ( const Block& self ) { return self.numberCosines(); },
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

} // block namespace
