struct AngularDistribution {

  int interpolationParameter;
  details::verify::CosineBins< std::vector< double > > cosineGrid;
  details::verify::Positive< std::vector< double > > pdf;
  details::verify::CDF< std::vector< double > > cdf;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/Builder.hpp"
};
