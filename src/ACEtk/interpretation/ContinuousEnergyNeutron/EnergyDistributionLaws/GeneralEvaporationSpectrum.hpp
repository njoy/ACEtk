class GeneralEvaporationSpectrum : public BaseLaw {
  Table::Slice theta_;
  Table::Slice tabulatedProbabilisticFunction_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/GeneralEvaporationSpectrum/src/ctor.hpp"

  using BaseLaw::interpolationParameters;
  using BaseLaw::incidentEnergies;
  auto theta() const{ return theta_; }
  auto tabulatedProbabilisticFunction() const{ 
    return tabulatedProbabilisticFunction_; }
  auto X() const{ return tabulatedProbabilisticFunction_; }
};
 typedef GeneralEvaporationSpectrum Law5;
