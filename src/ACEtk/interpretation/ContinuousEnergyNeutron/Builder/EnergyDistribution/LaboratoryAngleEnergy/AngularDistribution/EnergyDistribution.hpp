struct EnergyDistribution{
  int interpolationParameter;
  details::verify::Sorted< details::verify::Positive< 
      std::vector< double > > > energies;
  details::verify::Positive< std::vector< double > > pdf;
  details::verify::CDF< std::vector< double > > cdf;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder.hpp"
};
