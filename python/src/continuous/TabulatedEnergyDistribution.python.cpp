// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/TabulatedEnergyDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapTabulatedEnergyDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::TabulatedEnergyDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TabulatedEnergyDistribution",
    "Tabulated angular distribution data for a single incident energy or "
    "cosine value\n\n"
    "The TabulatedEnergyDistribution class contains the probability\n"
    "density function (PDF) and cumulative density function (CDF) as a function\n"
    "of the outgoing energy for the given incident energy or cosine value. It is\n"
    "used in the OutgoingEnergyDistributionData (ACE LAW 4 for a given incident\n"
    "energy) and in the OutgoingAngleEnergyDistributionData (ACE LAW 67 for a\n"
    "given cosine) in the DLW block."
  );

  // wrap the block
  block
  .def(

    python::init< double, int, std::vector< double >, std::vector< double >,
                  std::vector< double >, std::size_t >(),
    python::arg( "value" ), python::arg( "interpolation" ),
    python::arg( "cosines" ), python::arg( "pdf" ), python::arg( "cdf" ),
    python::arg( "discrete" ) = 0,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    incident    the incident energy or cosine value\n"
    "    outgoing    the outgoing energy values\n"
    "    pdf         the pdf values\n"
    "    cdf         the cdf values\n"
    "    discrete    the number of discrete photon lines (defaults to 0)"
  )
  .def_property_readonly(

    "energy_or_cosine",
    &Block::energyOrCosine,
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
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
