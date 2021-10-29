// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/FullyIsotropicDistribution.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapFullyIsotropicDistribution( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::FullyIsotropicDistribution;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "FullyIsotropicDistribution",
    "Convenience interface for when the angular distributions for a single\n"
    "reaction are isotropic for the entire incident energy range"
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
