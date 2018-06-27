class ContinuousTabular : public BaseLaw {

  std::vector< SecondaryDistribution > distributions_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/ContinuousTabular/src/ctor.hpp"

  using BaseLaw::interpolationParameters;
  using BaseLaw::incidentEnergies;
  auto distributions() const{ return distributions_; }

};

typedef ContinuousTabular Law4;
