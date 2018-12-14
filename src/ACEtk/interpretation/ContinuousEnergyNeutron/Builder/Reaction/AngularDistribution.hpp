struct AngularDistribution{
  details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > energyGrid;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder.hpp"
};
