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
    "The angular distribution is given in a different block\n\n"
    "The DistributionGivenElsewhere class contains contains no data. It is a\n"
    "convenience interface object used in the AND block."
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
