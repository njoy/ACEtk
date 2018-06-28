class EnergyDependentWattSpectrum {
  InterpolatedEnergies aParameters;
  Table::Slice aValues_;
  InterpolatedEnergies bParameters;
  Table::Slice bValues_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/EnergyDependentWattSpectrum/src/ctor.hpp"

  auto aInterpolationParameters() const { 
                           return aParameters.interpolationParameters(); }
  auto aEnergies() const { return aParameters.incidentEnergies(); }
  auto a() const { return aValues_; }
  auto bInterpolationParameters() const { 
                           return bParameters.interpolationParameters(); }
  auto bEnergies() const { return bParameters.incidentEnergies(); }
  auto b() const { return bValues_; }

};

typedef EnergyDependentWattSpectrum Law11;
