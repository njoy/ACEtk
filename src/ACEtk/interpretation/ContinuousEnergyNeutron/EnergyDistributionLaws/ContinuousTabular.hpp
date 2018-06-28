class ContinuousTabular : public InterpolatedEnergies {

  std::vector< SecondaryDistribution > distributions_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/ContinuousTabular/src/ctor.hpp"

  using InterpolatedEnergies::interpolationParameters;
  using InterpolatedEnergies::incidentEnergies;
  auto distributions() const{ return distributions_; }

};

typedef ContinuousTabular Law4;
