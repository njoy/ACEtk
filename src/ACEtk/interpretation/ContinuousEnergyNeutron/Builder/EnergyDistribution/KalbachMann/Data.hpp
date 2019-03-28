struct Data {
  int interpolationParameter;
  details::verify::Sorted< 
      details::verify::Positive< std::vector< double > > > energies;
  details::verify::Positive< std::vector< double > > pdf;
  details::verify::CDF< std::vector< double > > cdf;
  std::vector< double > precompoundFraction;
  std::vector< double > angularDistributionSlope;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/src/ACEify.hpp"
};
