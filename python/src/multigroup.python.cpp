// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace multigroup {
  

  // declarations - ACE table blocks
  void wrapIncidentParticleGroupStructureBlock( python::module&, python::module& );
  void wrapTotalCrossSectionBlock( python::module&, python::module& );
  void wrapFissionCrossSectionBlock( python::module&, python::module& );
  void wrapFissionChiDataBlock( python::module&, python::module& );
  void wrapAbsorptionCrossSectionBlock( python::module&, python::module& );
  void wrapStoppingPowerBlock( python::module&, python::module& );
  void wrapMomentumTransferBlock( python::module&, python::module& );
  void wrapEditCrossSectionBlock( python::module&, python::module& );
}

void wrapMultigroup( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "multigroup",
    "Multigroup MC ACE blocks and components"
  );

  multigroup::wrapIncidentParticleGroupStructureBlock( submodule, viewmodule );
  multigroup::wrapTotalCrossSectionBlock( submodule, viewmodule );
  multigroup::wrapFissionCrossSectionBlock( submodule, viewmodule );
  multigroup::wrapFissionChiDataBlock( submodule, viewmodule );
  multigroup::wrapAbsorptionCrossSectionBlock( submodule, viewmodule );
  multigroup::wrapStoppingPowerBlock( submodule, viewmodule );
  multigroup::wrapMomentumTransferBlock( submodule, viewmodule );
  multigroup::wrapEditCrossSectionBlock( submodule, viewmodule );
}
