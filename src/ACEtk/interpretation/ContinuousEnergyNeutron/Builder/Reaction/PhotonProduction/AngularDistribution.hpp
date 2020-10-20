struct AngularDistribution {

  using cosArray = dvCB< std::array< double, 33 > >;

  dvP< dvS< std::vector< double > > > energyGrid;
  std::map< int, std::optional< cosArray > > cosineBins;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/AngularDistribution/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/AngularDistribution/src/ACEify.hpp"
};
