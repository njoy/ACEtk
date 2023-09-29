// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/TabulatedAngleEnergyDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapTabulatedAngleEnergyDistribution( python::module& module,
                                           python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::TabulatedAngleEnergyDistribution;
  using Distribution = njoy::ACEtk::block::TabulatedEnergyDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TabulatedAngleEnergyDistribution",
    "Tabulated outgoing energy and angle distribution data for a single incident energy\n\n"
    "The TabulatedAngleEnergyDistribution class contains the tabulated outgoing\n"
    "energy distributions for a set of cosine values and associated incident\n"
    "energy value. It is used in the AngleEnergyDistributionData (ACE LAW 67)\n"
    "in the DLW block."
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

    "NC",
    &Block::NC,
    "The number of cosine values"
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
  .def(

    "cosine",
    &Block::cosine,
    python::arg( "index" ),
    "Return the cosine for a given index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "LOCC",
    &Block::LOCC,
    python::arg( "index" ),
    "Return the the distribution locator for a cosine index\n\n"
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
    "Return the the distribution locator for a cosine index\n\n"
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
    "Return the relative distribution locator for a cosine index\n\n"
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
    "Return the distribution data for a cosine index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
