struct AngularDistribution {

  details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > energyGrid;
  std::vector<
    details::verify::Positive< std::array< double, 33 > > > cosineBins;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution/Builder.hpp"
};