// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace dosimetry {

  // declarations - ACE data components
  void wrapDosimetryCrossSectionData( python::module&, python::module& );

  // declarations - ACE table blocks
  void wrapDosimetryCrossSectionBlock( python::module&, python::module& );
}

void wrapDosimetry( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "dosimetry",
    "Dosimetry ACE blocks and components"
  );

  dosimetry::wrapDosimetryCrossSectionData( submodule, viewmodule );
  dosimetry::wrapDosimetryCrossSectionBlock( submodule, viewmodule );
}
