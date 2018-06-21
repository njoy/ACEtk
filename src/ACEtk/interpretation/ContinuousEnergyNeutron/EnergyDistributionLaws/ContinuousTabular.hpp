class ContinuousTabular {

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/ContinuousTabular/Distribution.hpp"

private:
  ENDFInterpolationParameters interpolationParameters_;
  Table::Slice incidentEnergies_;
  std::vector< Distribution > distributions_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/ContinuousTabular/src/ctor.hpp"

  auto interpolationParameters() const { return interpolationParameters_; }
  auto incidentEnergies() const { return incidentEnergies_; }
  auto distributions() const{ return distributions_; }

};

typedef ContinuousTabular Law4;
