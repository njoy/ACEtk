class EvaporationSpectrum : public InterpolatedEnergies {
  double restrictionEnergy_;
  Table::Slice theta_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/EvaporationSpectrum/src/ctor.hpp"

  using InterpolatedEnergies::interpolationParameters;
  using InterpolatedEnergies::incidentEnergies;
  auto theta() const{ return theta_; }
  double restrictionEnergy() const{ return restrictionEnergy_; }
  double U() const{ return restrictionEnergy_; }
};

typedef EvaporationSpectrum Law9;
