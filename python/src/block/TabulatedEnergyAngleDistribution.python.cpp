// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/TabulatedEnergyAngleDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapTabulatedEnergyAngleDistribution( python::module& module,
                                           python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::TabulatedEnergyAngleDistribution;
  using Distribution = njoy::ACEtk::block::TabulatedAngularDistributionWithProbability;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TabulatedEnergyAngleDistribution",
    "Tabulated outgoing energy and angle distribution data for a single incident energy\n\n"
    "The TabulatedEnergyAngleDistribution class contains the tabulated angular\n"
    "distributions for a set of outgoing energy values and associated incident\n"
    "energy value. It is used in the OutgoingEnergyAngleDistributionData\n"
    "(ACE LAW 61) in the DLW block."
  );

  // wrap the block
  block
  .def(

    python::init< double, int, std::vector< Distribution >, std::size_t >(),
    python::arg( "incident" ), python::arg( "interpolation" ),
    python::arg( "distributions" ), python::arg( "locb" ) = 1,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    incident         the incident energy value\n"
    "    interpolation    the interpolation type\n"
    "    distributions    the distributions for each outgoing energy\n"
    "    locb             the starting xss index with respect to the DLW block\n"
    "                     (default = 1, the relative locators get recalculated)"
  )
  .def_property_readonly(

    "incident_energy",
    &Block::incidentEnergy,
    "The incident energy value"
  )
  .def_property_readonly(

    "interpolation",
    &Block::interpolation,
    "The interpolation type"
  )
  .def_property_readonly(

    "NE",
    &Block::NE,
    "The number of outgoing energy values"
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
    "The associated probability values"
  )
  .def_property_readonly(

    "cdf",
    [] ( const Block& self ) -> DoubleRange
       { return self.cdf(); },
    "The associated cumulative probability values"
  )
  .def(

    "outgoing_energy",
    &Block::outgoingEnergy,
    python::arg( "index" ),
    "Return the outgoing energy for a given index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "probability",
    &Block::probability,
    python::arg( "index" ),
    "Return the probability for a given index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "cumulative_probability",
    &Block::cumulativeProbability,
    python::arg( "index" ),
    "Return the cumulative probability for a given index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "LOCC",
    &Block::LOCC,
    python::arg( "index" ),
    "Return the the distribution locator for an outgoing energy index\n\n"
    "This locator is the value as stored in the XSS array. It is relative to\n"
    "the beginning of the DLW block.\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "distribution_locator",
    &Block::distributionLocator,
    python::arg( "index" ),
    "Return the the distribution locator for an outgoing energy index\n\n"
    "This locator is the value as stored in the XSS array. It is relative to\n"
    "the beginning of the DLW block.\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "relative_distribution_locator",
    &Block::relativeDistributionLocator,
    python::arg( "index" ),
    "Return the relative distribution locator for an outgoing energy index\n\n"
    "This is the locator relative to the beginning of the current angular\n"
    "distribution block in the DLW block. It is always positive.\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "distributions",
    &Block::distributions,
    "The distributions"
  )
  .def(

    "distribution",
    &Block::distribution,
    python::arg( "index" ),
    "Return the distribution data for an outgoing energy index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
