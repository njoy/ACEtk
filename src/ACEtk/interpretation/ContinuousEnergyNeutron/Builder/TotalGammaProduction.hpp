struct TotalGammaProduction{
  std::vector< double > crossSection;
  std::array< std::array< double, 20 >, 30 > outgoingEnergies;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction/Builder.hpp"
};
