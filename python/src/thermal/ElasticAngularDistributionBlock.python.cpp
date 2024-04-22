// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/thermal/ElasticAngularDistributionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace thermal {

void wrapElasticAngularDistributionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::thermal::ElasticAngularDistributionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ElasticAngularDistributionBlock",
    "The angular distribution block for inelastic thermal scattering\n\n"
    "The ElasticAngularDistributionBlock class contains the equiprobable set or\n"
    "a skewed distribution of discrete cosines, or a tabulated probability distribution."
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
  .def_property_readonly(

    "NCL",
    &Block::NCL,
    "The elastic dimensioning parameter\n\n"
    "The elastic dimensioning parameter is equal to NC - 1"
  )
  .def_property_readonly(

    "elastic_dimensioning_parameter",
    &Block::elasticDimensioningParameter,
    "The elastic dimensioning parameter\n\n"
    "The elastic dimensioning parameter is equal to NC - 1"
  )
  .def(

    "cosines",
    [] ( const Block& self, std::size_t index ) -> DoubleRange
       { return self.cosines( index ); },
    python::arg( "index" ),
    "The cosine values for an incident energy index\n\n"
    "When the index is out of range an std::out_of_range exception is thrown\n"
    "(debug mode only).\n\n"
    "index    the incident energy index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // thermal namespace
