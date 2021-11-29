// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/MultiDistributionData.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapMultiDistributionData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::MultiDistributionData;
  using DistributionProbability = njoy::ACEtk::block::DistributionProbability;
  using DistributionData = Block::DistributionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "MultiDistributionData",
    "Convenience interface for outgoing energy distribution data from the\n"
    "DLW block for a single reaction using multiple distributions"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< DistributionProbability >,
                  std::vector< DistributionData >,
                  std::size_t >(),
    python::arg( "probabilities" ), python::arg( "distributions" ),
    python::arg( "locb" ) = 1,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    probabilities    the probabilities\n"
    "    distributions    the distributions\n"
    "    locb             the starting xss index with respect to the superblock\n"
    "                     (default = 1, the relative locators get recalculated)"
  )
  .def_property_readonly(

    "LAW",
    [] ( const Block& self ) { return self.LAW(); },
    "The distribution type"
  )
  .def_property_readonly(

    "type",
    [] ( const Block& self ) { return self.type(); },
    "The distribution type"
  )
  .def_property_readonly(

    "number_distributions",
    &Block::numberDistributions,
    "The number of distributions"
  )
  .def_property_readonly(

    "probabilities",
    &Block::probabilities,
    "The probability data for each distribution"
  )
  .def(

    "probability",
    &Block::probability,
    python::arg( "index" ),
    "Return the probability data for a distribution index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "distributions",
    &Block::distributions,
    "The distribution data for each distribution"
  )
  .def(

    "distribution",
    &Block::distribution,
    python::arg( "index" ),
    "Return the distribution data for a distribution index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
