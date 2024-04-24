// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/EnergyDistributionType.hpp"

// namespace aliases
namespace python = pybind11;

void wrapEnergyDistributionType( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ACEtk::EnergyDistributionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "EnergyDistributionType",
    "The energy distribution types",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Equiprobable",            Component::Equiprobable )
  .value( "DiscretePhoton",          Component::DiscretePhoton )
  .value( "LevelScattering",         Component::LevelScattering )
  .value( "TabulatedEnergy",         Component::TabulatedEnergy )
  .value( "GeneralEvaporation",      Component::GeneralEvaporation )
  .value( "SimpleMaxwellianFission", Component::SimpleMaxwellianFission )
  .value( "Evaporation",             Component::Evaporation )
  .value( "Watt",                    Component::Watt )
  .value( "TwoBodyTransfer",         Component::TwoBodyTransfer )
  .value( "KalbachMann",             Component::KalbachMann )
  .value( "TabulatedEnergyAngle",    Component::TabulatedEnergyAngle )
  .value( "NBodyPhaseSpace",         Component::NBodyPhaseSpace )
  .value( "TabulatedAngleEnergy",    Component::TabulatedAngleEnergy )
  .value( "MultiDistribution",       Component::MultiDistribution );
}
