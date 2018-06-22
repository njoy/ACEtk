class BaseLaw {
protected:
  ENDFInterpolationParameters interpolationParameters_;
  Table::Slice incidentEnergies_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/BaseLaw/src/ctor.hpp"

  auto interpolationParameters() const { return interpolationParameters_; }
  auto incidentEnergies() const { return incidentEnergies_; }
};
