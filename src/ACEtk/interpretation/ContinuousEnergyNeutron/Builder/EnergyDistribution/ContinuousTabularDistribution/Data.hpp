struct Data{

  int interpolationParameter;
  details::verify::Sorted< 
      details::verify::Positive< std::vector< double > > > energies;
  details::verify::Positive< std::vector< double > > pdf;
  details::verify::CDF< std::vector< double > > cdf;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder.hpp"
};
