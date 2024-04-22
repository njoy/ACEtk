// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace thermal {

  // declarations - ACE data components
  void wrapDiscreteCosines( python::module&, python::module& );
  void wrapDiscreteCosinesWithProbability( python::module&, python::module& );

  // declarations - ACE table blocks
  void wrapCrossSectionBlock( python::module&, python::module& );
  void wrapElasticAngularDistributionBlock( python::module&, python::module& );
  void wrapInelasticAngularDistributionBlock( python::module&, python::module& );
}

void wrapThermal( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "thermal",
    "Thermal scattering ACE blocks and components"
  );

  thermal::wrapDiscreteCosines( submodule, viewmodule );
  thermal::wrapDiscreteCosinesWithProbability( submodule, viewmodule );
  thermal::wrapCrossSectionBlock( submodule, viewmodule );
  thermal::wrapElasticAngularDistributionBlock( submodule, viewmodule );
  thermal::wrapInelasticAngularDistributionBlock( submodule, viewmodule );
}
