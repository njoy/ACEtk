// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapThermalScatteringInelasticAngularDistributionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ThermalScatteringInelasticAngularDistributionBlock;
  using DiscreteCosines = njoy::ACEtk::block::ThermalScatteringDiscreteCosines;
  using DiscreteCosinesWithProbability = njoy::ACEtk::block::ThermalScatteringDiscreteCosinesWithProbability;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ThermalScatteringInelasticAngularDistributionBlock",
    "The angular distribution block for inelastic thermal scattering\n\n"
    "The ThermalScatteringInelasticAngularDistributionBlock class contains\n"
    "the equiprobable set or a skewed distribution of discrete cosines, or a\n"
    "tabulated probability distribution."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< std::vector< DiscreteCosines > >, bool, std::size_t >(),
    python::arg( "cosines" ), python::arg( "skewed" ), python::arg( "locb" ) = 1,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    cosines     the discrete cosine data for each incident and outgoing energy value\n"
    "    skewed      flag to indicate whether or not the distribution is skewed or equiprobable\n"
    "    locb        the starting xss index for the ITXE block (default = 1)"
  )
  .def(

    python::init< std::vector< std::vector< DiscreteCosinesWithProbability > >,
                  std::size_t >(),
    python::arg( "cosines" ), python::arg( "locb" ) = 1,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    cosines     the discrete cosine data for each incident and outgoing energy value\n"
    "    locb        the starting xss index for the ITXE block (default = 1)"
  )
  .def_property_readonly(

    "IFENG",
    &Block::IFENG,
    "The secondary energy mode"
  )
  .def_property_readonly(

    "secondary_energy_mode",
    &Block::secondaryEnergyMode,
    "The number of discrete cosines"
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

    "NIL",
    &Block::NIL,
    "The inelastic dimensioning parameter\n\n"
    "For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,\n"
    "for IFENG = 2 this will be equal to NC + 1\n"
  )
  .def_property_readonly(

    "inelastic_dimensioning_parameter",
    &Block::inelasticDimensioningParameter,
    "The inelastic dimensioning parameter\n\n"
    "For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,\n"
    "for IFENG = 2 this will be equal to NC + 1\n"
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
  .def(

    "NIEB",
    &Block::NIEB,
    python::arg( "index" ),
    "The number of secondary energies for an incident energy index\n\n"
    "When the index is out of range an std::out_of_range exception is thrown\n"
    "(debug mode only).\n\n"
    "index    the incident energy index (one-based)"
  )
  .def(

    "number_outgoing_energies",
    &Block::numberOutgoingEnergies,
    python::arg( "index" ),
    "The number of secondary energies for an incident energy index\n\n"
    "When the index is out of range an std::out_of_range exception is thrown\n"
    "(debug mode only).\n\n"
    "index    the incident energy index (one-based)"
  )
  .def_property_readonly(

    "data",
    &Block::data,
    "The angular distribution data"
  )
  .def(

    "discrete_cosine_data",
    &Block::discreteCosineData,
    python::arg( "incident" ), python::arg( "outgoing" ),
    "The discrete cosine data for an incident and outgoing energy index\n\n"
    "When the index is out of range an std::out_of_range exception is thrown\n"
    "(debug mode only).\n\n"
    "incident    the incident energy index (one-based)\n"
    "outgoing    the outgoing energy index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
