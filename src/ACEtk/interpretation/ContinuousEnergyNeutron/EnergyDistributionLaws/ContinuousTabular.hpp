class ContinuousTabular : public BaseLaw {

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/ContinuousTabular/Distribution.hpp"

private:
  std::vector< Distribution > distributions_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/ContinuousTabular/src/ctor.hpp"

  using BaseLaw::interpolationParameters;
  using BaseLaw::incidentEnergies;
  auto distributions() const{ return distributions_; }

};

typedef ContinuousTabular Law4;
