class SecondaryDistribution {
  int interpolationParameter_;
  Table::Slice energyGrid_;
  CoupledDensityFunctions densityFunctions_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/SecondaryDistribution/src/ctor.hpp"

  auto interpolationParameter() const { return interpolationParameter_; }

  auto energyGrid() const{ return energyGrid_; }

  auto PDF() const { return densityFunctions_.PDF(); }
  auto CDF() const { return densityFunctions_.CDF(); }
};
