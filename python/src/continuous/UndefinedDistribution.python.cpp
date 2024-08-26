// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/UndefinedDistribution.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapUndefinedDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::UndefinedDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "UndefinedDistribution",
    "The distribution is undefined\n\n"
    "The UndefinedDistribution class contains contains no data. It is a\n"
    "convenience interface object used in the DLWH block when no energy\n"
    "distribution data is given."
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

} // continuous namespace
