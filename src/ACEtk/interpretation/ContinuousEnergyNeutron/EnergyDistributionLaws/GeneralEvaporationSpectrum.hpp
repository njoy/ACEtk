class GeneralEvaporationSpectrum : public InterpolatedEnergies {
  Table::Slice theta_;
  Table::Slice tabulatedProbabilisticFunction_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/GeneralEvaporationSpectrum/src/ctor.hpp"

  using InterpolatedEnergies::interpolationParameters;
  using InterpolatedEnergies::incidentEnergies;
  auto theta() const{ return theta_; }
  auto tabulatedProbabilisticFunction() const{ 
    return tabulatedProbabilisticFunction_; }
  auto X() const{ return tabulatedProbabilisticFunction_; }
};
 typedef GeneralEvaporationSpectrum Law5;
