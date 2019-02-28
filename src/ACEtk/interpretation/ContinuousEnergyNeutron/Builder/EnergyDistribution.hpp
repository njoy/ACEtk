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
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum.hpp" // LAW=9
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum.hpp" // LAW=11
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions.hpp" // LAW=22
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LAW24.hpp" // LAW=24
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann.hpp" // LAW=44
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution.hpp" // LAW=61
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/NBodyPhaseSpace.hpp" // LAW=66
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy.hpp" // LAW=67

  using LAWS = std::variant< 
    TabularEquiprobableEnergyBins,    // LAW=1
    DiscretePhotonEnergy,             // LAW=2
    LevelScattering,                  // LAW=3
    ContinuousTabularDistribution,    // LAW=4
    GeneralEvaporationSpectrum,       // LAW=5
    SimpleMaxwellianFissionSpectrum,  // LAW=7
    EvaporationSpectrum,              // LAW=9
    EnergyDependentWattSpectrum,      // LAW=11
    TabularLinearFunctions,           // LAW=22
    LAW24,                            // LAW=24
    KalbachMann,                      // LAW=44
    KalbachMannAngularDistribution,   // LAW=61
    NBodyPhaseSpace,                  // LAW=66
    LaboratoryAngleEnergy             // LAW=67
    // EnergyDependentNeutronYields
                           >;

  Tabulated1D tab1;
  LAWS law;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder.hpp"
};
