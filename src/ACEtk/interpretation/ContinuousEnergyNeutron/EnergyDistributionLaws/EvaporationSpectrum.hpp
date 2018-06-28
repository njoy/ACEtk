class EvaporationSpectrum : public BaseLaw {
  double restrictionEnergy_;
  Table::Slice theta_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/EvaporationSpectrum/src/ctor.hpp"

  using BaseLaw::interpolationParameters;
  using BaseLaw::incidentEnergies;
  auto theta() const{ return theta_; }
  double restrictionEnergy() const{ return restrictionEnergy_; }
  double U() const{ return restrictionEnergy_; }
};

typedef EvaporationSpectrum Law9;
