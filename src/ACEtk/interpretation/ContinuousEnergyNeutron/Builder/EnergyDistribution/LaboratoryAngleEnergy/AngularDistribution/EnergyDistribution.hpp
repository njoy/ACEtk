struct EnergyDistribution{

  int interpolationParameter;
  dvS< dvP< 
      std::vector< double > > > energies;
  dvP< std::vector< double > > pdf;
  dvC< std::vector< double > > cdf;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/src/ACEify.hpp"
};
