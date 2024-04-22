// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/TabulatedKalbachMannDistribution.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapTabulatedKalbachMannDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::TabulatedKalbachMannDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TabulatedKalbachMannDistribution",
    "Tabulated Kalbach-Mann distribution data for a single incident energy\n\n"
    "The TabulatedKalbachMannDistribution class contains the probability\n"
    "density function (PDF), the cumulative density function (CDF), the\n"
    "precompound fraction r and angular distribution slope a as a function\n"
    "of the outgoing energy for a single incident energy. It is\n"
    "used in the KalbachMannDistributionData (ACE LAW 44 for a given incident\n"
    "energy) in the DLW block."
  );

  // wrap the block
  block
  .def(

    python::init< double, int, std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double >,
                  std::vector< double >, std::size_t >(),
    python::arg( "incident" ), python::arg( "interpolation" ),
    python::arg( "cosines" ), python::arg( "pdf" ), python::arg( "cdf" ),
    python::arg( "r" ), python::arg( "a" ), python::arg( "discrete" ) = 0,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    incident    the incident energy value\n"
    "    cosines     the cosine values\n"
    "    pdf         the pdf values\n"
    "    cdf         the cdf values\n"
    "    r           the precompound fraction values values\n"
    "    a           the angular distribution slope values\n"
    "    discrete    the number of discrete photon lines (defaults to 0)"
  )
  .def_property_readonly(

    "incident_energy",
    &Block::incidentEnergy,
    "The incident energy"
  )
  .def_property_readonly(

    "interpolation",
    &Block::interpolation,
    "The interpolation flag"
  )
  .def_property_readonly(

    "number_discrete_photon_lines",
    &Block::numberDiscretePhotonLines,
    "The number of discrete photon lines"
  )
  .def_property_readonly(

    "number_outgoing_energies",
    &Block::numberOutgoingEnergies,
    "The number of outgoing energy values"
  )
  .def_property_readonly(

    "outgoing_energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.outgoingEnergies(); },
    "The outgoing energy values"
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
  )
  .def_property_readonly(

    "precompound_fraction_values",
    [] ( const Block& self ) -> DoubleRange
       { return self.precompoundFractionValues(); },
    "The precompound fraction values"
  )
  .def_property_readonly(

    "angular_distribution_slope_values",
    [] ( const Block& self ) -> DoubleRange
       { return self.angularDistributionSlopeValues(); },
    "The angular distribution slope values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
