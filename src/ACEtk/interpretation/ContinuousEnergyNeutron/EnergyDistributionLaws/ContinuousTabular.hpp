class ContinuousTabular {

  ENDFInterpolationParameters interpolationParameters_;
  Table::Slice incidentEnergies_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/ContinuousTabular/src/ctor.hpp"
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/ContinuousTabular/Distribution.hpp"

  auto interpolationParameters() const { return interpolationParameters_; }
  auto incidentEnergies() const { return incidentEnergies_; }

};

typedef ContinuousTabular Law4;
