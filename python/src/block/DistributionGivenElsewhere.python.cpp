// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/DistributionGivenElsewhere.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapDistributionGivenElsewhere( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::DistributionGivenElsewhere;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "DistributionGivenElsewhere",
    "Convenience interface for when the angular distributions for a single\n"
    "reaction are given in the DLW block"
  );

  // wrap the block
  block
  .def(

    python::init<>(),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self    the block"
  );
}

} // block namespace
