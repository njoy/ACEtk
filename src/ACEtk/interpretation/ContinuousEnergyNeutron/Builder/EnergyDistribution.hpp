struct EnergyDistribution : 
  protected ContinuousEnergyNeutron::Builder::Tabulated<
    std::pair< double, EnergyDistributions::LAWS > >{

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder.hpp"
};
