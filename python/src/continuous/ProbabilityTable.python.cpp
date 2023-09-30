// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/ProbabilityTable.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapProbabilityTable( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::ProbabilityTable;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ProbabilityTable",
    "An unresolved resonance probability table for a single incident energy value\n\n"
    "The ProbabilityTable class contains the probabilities and associated\n"
    "values for the total, elastic, fission and capture cross sections and the\n"
    "heating numbers."
  );

  // wrap the block
  block
  .def(

    python::init< double, std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "incident" ), python::arg( "probabilities" ),
    python::arg( "total" ), python::arg( "elastic" ),
    python::arg( "capture" ), python::arg( "heating" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    incident         the incident energy value\n"
    "    probabilities    the probability values\n"
    "    total            the total cross section values\n"
    "    elastic          the elastic cross section values\n"
    "    capture          the capture cross section values\n"
    "    heating          the heating numbers"
  )
  .def(

    python::init< double, std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "incident" ), python::arg( "probabilities" ),
    python::arg( "total" ), python::arg( "elastic" ), python::arg( "fission" ),
    python::arg( "capture" ), python::arg( "heating" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    incident         the incident energy value\n"
    "    probabilities    the probability values\n"
    "    total            the total cross section values\n"
    "    elastic          the elastic cross section values\n"
    "    fission          the fission cross section values\n"
    "    capture          the capture cross section values\n"
    "    heating          the heating numbers"
  )
  .def_property_readonly(

    "incident_energy",
    &Block::incidentEnergy,
    "The incident energy value"
  )
  .def_property_readonly(

    "number_bins",
    &Block::numberBins,
    "The number of bins in the table"
  )
  .def_property_readonly(

    "cumulative_probabilities",
    [] ( const Block& self ) -> DoubleRange
       { return self.cumulativeProbabilities(); },
    "The cumulative probability values"
  )
  .def_property_readonly(

    "total",
    [] ( const Block& self ) -> DoubleRange
       { return self.total(); },
    "The total cross section values"
  )
  .def_property_readonly(

    "elastic",
    [] ( const Block& self ) -> DoubleRange
       { return self.elastic(); },
    "The elastic cross section values"
  )
  .def_property_readonly(

    "fission",
    [] ( const Block& self ) -> DoubleRange
       { return self.fission(); },
    "The fission cross section values"
  )
  .def_property_readonly(

    "capture",
    [] ( const Block& self ) -> DoubleRange
       { return self.capture(); },
    "The capture cross section values"
  )
  .def_property_readonly(

    "heating",
    [] ( const Block& self ) -> DoubleRange
       { return self.heating(); },
    "The average heating cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
