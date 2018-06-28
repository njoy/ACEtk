class LaboratoryAngleEnergyLaw : public InterpolatedEnergies {

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/LaboratoryAngleEnergyLaw/AngularDistribution.hpp"

private:
  std::vector< AngularDistribution > angularDistributions_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/LaboratoryAngleEnergyLaw/src/ctor.hpp"

  using InterpolatedEnergies::interpolationParameters;
  using InterpolatedEnergies::incidentEnergies;

  auto angularDistributions() const { return angularDistributions_; }
  auto NMU() const{ return angularDistributions_.size(); }
};

typedef LaboratoryAngleEnergyLaw Law67;
