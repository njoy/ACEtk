class AngularDistribution {

  int interpolationParameter_;
  Table::Slice energyGrid_;
  std::vector< SecondaryDistribution > cosineDistributions_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/LaboratoryAngleEnergyLaw/AngularDistribution/src/ctor.hpp"

  auto interpolationParameter() const { return interpolationParameter_; }
  auto INTMU() const { return interpolationParameter_; }

  auto energyGrid() const { return energyGrid_; }

  auto cosineDistributions() const{ return cosineDistributions_; }
};
