struct EnergyDistribution {

  template<  typename ParentBuilder >
  class Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Base.hpp" 

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins.hpp" // LAW=1
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy.hpp" // LAW=2
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering.hpp" // LAW=3
  // #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution.hpp" // LAW=4

  using LAWS = std::variant< 
    TabularEquiprobableEnergyBins, // LAW=1
    DiscretePhotonEnergy,          // LAW=2
    LevelScattering                // LAW=3
    // ContinuousTabularDistribution  // LAW=4
                           >;

  using lawTab = Tabulated< std::pair< double, LAWS > >;
  lawTab tabulated;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder.hpp"
};
