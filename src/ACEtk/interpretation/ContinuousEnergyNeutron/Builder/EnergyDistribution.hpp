struct EnergyDistribution{

  template<  typename ParentBuilder >
  class Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Base.hpp" 

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins.hpp" // LAW=1
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy.hpp" // LAW=2
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering.hpp" // LAW=3
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution.hpp" // LAW=4
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum.hpp" // LAW=5
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum.hpp" // LAW=7

  using EvaporationSpectrum = SimpleMaxwellianFissionSpectrum; // LAW=9

  using LAWS = std::variant< 
    TabularEquiprobableEnergyBins,    // LAW=1
    DiscretePhotonEnergy,             // LAW=2
    LevelScattering,                  // LAW=3
    ContinuousTabularDistribution,    // LAW=4
    GeneralEvaporationSpectrum,       // LAW=5
    SimpleMaxwellianFissionSpectrum,  // LAW=7
    EvaporationSpectrum               // LAW=9
                           >;

  Tabulated1D tab1;
  LAWS law;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder.hpp"
};
