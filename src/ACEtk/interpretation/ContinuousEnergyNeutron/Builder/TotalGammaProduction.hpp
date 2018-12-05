struct TotalGammaProduction{
  std::vector< double > crossSection;
  std::optional< std::array<
    details::verify::Positive< 
      std::array< double, 20 > >, 30 > > outgoingEnergies_;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction/Builder.hpp"
};
