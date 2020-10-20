struct TotalGammaProduction{
  std::vector< double > crossSection;
  std::optional< std::array<
    dvP< 
      std::array< double, 20 > >, 30 > > outgoingEnergies;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction/Builder.hpp"
};
