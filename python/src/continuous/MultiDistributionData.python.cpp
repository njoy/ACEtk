// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/MultiDistributionData.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapMultiDistributionData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::MultiDistributionData;
  using DistributionProbability = njoy::ACEtk::continuous::DistributionProbability;
  using DistributionData = Block::DistributionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "MultiDistributionData",
    "The distribution is a combination of multiple distributions\n\n"
    "The MultiDistributionData class contains a set of distributions and\n"
    "associated probabilities to represent the particle's distribution data.\n"
    "This type of distribution is rarely used, and when it happens it is often\n"
    "used for higher chance fission spectra. It is used in the DLW block (there\n"
    "is no ACE LAW associated to this distribution type, but internally in ACEtk\n"
    "we refer to it as ACE LAW 666 because it is evil)."
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

} // continuous namespace
