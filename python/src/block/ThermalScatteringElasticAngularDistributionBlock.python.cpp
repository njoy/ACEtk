// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ThermalScatteringElasticAngularDistributionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapThermalScatteringElasticAngularDistributionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ThermalScatteringElasticAngularDistributionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ThermalScatteringElasticAngularDistributionBlock",
    "The angular distribution block for inelastic thermal scattering\n\n"
    "The ThermalScatteringElasticAngularDistributionBlock class contains\n"
    "the equiprobable set or a skewed distribution of discrete cosines, or a\n"
    "tabulated probability distribution."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< std::vector< double > > >(),
    python::arg( "cosines" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    cosines     the discrete cosine values for each incident energy"
  )
  .def_property_readonly(

    "NE",
    &Block::NE,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "number_incident_energies",
    &Block::numberIncidentEnergies,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "NC",
    &Block::NC,
    "The number of equiprobable discrete cosine values for each incident and "
    "outgoing energy pair"
  )
  .def_property_readonly(

    "number_discrete_cosines",
    &Block::numberDiscreteCosines,
    "The number of equiprobable discrete cosine values for each incident and "
    "outgoing energy pair"
  )
  .def(

    "cosines",
    &Block::cosines,
    python::arg( "index" ),
    "The cosine values for an incident energy index\n\n"
    "When the index is out of range an std::out_of_range exception is thrown\n"
    "(debug mode only).\n\n"
    "index    the incident energy index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
