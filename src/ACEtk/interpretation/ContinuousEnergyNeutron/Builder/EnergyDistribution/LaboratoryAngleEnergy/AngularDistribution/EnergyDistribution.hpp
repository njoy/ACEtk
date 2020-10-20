struct EnergyDistribution{

  int interpolationParameter;
  dvP< dvS< std::vector< double > > > energies;
  dvP< std::vector< double > > pdf;
  dvC< std::vector< double > > cdf;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/src/ACEify.hpp"
};
