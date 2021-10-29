// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/AngularDistributionData.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapAngularDistributionData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::AngularDistributionData;
  using Distribution = Block::Distribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "AngularDistributionData",
    "Convenience interface for angular distribution data for a single reaction "
    "from the AND block"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< Distribution >&&, std::size_t >(),
    python::arg( "distributions" ), python::arg( "locb" ) = 1,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    distributions    the angular distributions for each incident energy\n"
    "    locb             the starting xss index with respect to the AND block\n"
    "                     (default = 1, the relative locators get recalculated)"
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

    "incident_energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.incidentEnergies(); },
    "The incident energy values"
  )
  .def(

    "incident_energy",
    &Block::incidentEnergy,
    python::arg( "index" ),
    "Return the incident energy for a given index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "LOCC",
    &Block::LOCC,
    python::arg( "index" ),
    "Return the the angular distribution locator for an incident energy index\n\n"
    "This locator is the value as stored in the XSS array. It is relative to\n"
    "the beginning of the AND block. The distribution type is determined from\n"
    "the sign of the locator:\n"
    "  - when the value if negative, it is a tabulated distribution\n"
    "  - when the value if positive, it is an equiprobable distribution\n"
    "  - when the value if zero, it is an isotropic distribution\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "angular_distribution_locator",
    &Block::angularDistributionLocator,
    python::arg( "index" ),
    "Return the angular distribution locator for an incident energy index\n\n"
    "This locator is the value as stored in the XSS array. It is relative to\n"
    "the beginning of the AND block. The distribution type is determined from\n"
    "the sign of the locator:\n"
    "  - when the value if negative, it is a tabulated distribution\n"
    "  - when the value if positive, it is an equiprobable distribution\n"
    "  - when the value if zero, it is an isotropic distribution\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "relative_angular_distribution_locator",
    &Block::relativeAngularDistributionLocator,
    python::arg( "index" ),
    "Return the relative angular distribution locator for an incident energy index\n\n"
    "This is the locator relative to the beginning of the current angular\n"
    "distribution block in the AND block. It is always positive.\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "angular_distribution_type",
    &Block::angularDistributionType,
    python::arg( "index" ),
    "Return the angular distribution type for an incident energy index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "angular_distribution_data",
    &Block::angularDistributionData,
    python::arg( "index" ),
    "Return the angular distribution data for an incident energy index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
