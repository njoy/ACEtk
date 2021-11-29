// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/TabulatedOutgoingEnergyDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapTabulatedOutgoingEnergyDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::TabulatedOutgoingEnergyDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TabulatedOutgoingEnergyDistribution",
    "Convenience interface for tabulated outgoing energy distribution data "
    "from the DLW block"
  );

  // wrap the block
  block
  .def(

    python::init< double, int, std::vector< double >, std::vector< double >,
                  std::vector< double >, std::size_t >(),
    python::arg( "incident" ), python::arg( "interpolation" ),
    python::arg( "cosines" ), python::arg( "pdf" ), python::arg( "cdf" ),
    python::arg( "discrete" ) = 0,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    incident    the incident energy value\n"
    "    cosines     the cosine values\n"
    "    pdf         the pdf values\n"
    "    cdf         the cdf values\n"
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
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
