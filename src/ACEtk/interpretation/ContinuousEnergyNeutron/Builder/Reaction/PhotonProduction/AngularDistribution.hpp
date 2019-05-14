struct AngularDistribution {

  dvP< 
    dvS< std::vector< double > > > energyGrid;
  std::vector<
    dvP< std::array< double, 33 > > > cosineBins;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/AngularDistribution/Builder.hpp"
};
