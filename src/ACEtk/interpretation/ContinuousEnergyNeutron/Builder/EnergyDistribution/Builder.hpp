template<  typename ParentBuilder >
class Builder: 
  public Tabulated1D::Builder< Builder< ParentBuilder > >{

  using BaseBuilder = Tabulated1D::Builder< Builder< ParentBuilder > >;

  std::optional< LAWS > law_;

  template< typename Derived, typename PB >
  friend class Base::Builder;
  
protected:
  std::reference_wrapper< ParentBuilder > parent;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/addEnergyDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/construct.hpp"

public:

  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addEnergyDistribution( this->construct() );
  }

  // LAW=1
  TabularEquiprobableEnergyBins::Builder< Builder >
  tabularEquiprobableEnergyBins(){ return { *this }; }
  // LAW=2
  DiscretePhotonEnergy::Builder< Builder >
  discretePhotonEnergy( ){ return { *this }; }
  // LAW=3
  LevelScattering::Builder< Builder >
  levelScattering( ){ return { *this }; }
  // LAW=4
  ContinuousTabularDistribution::Builder< Builder >
  continuousTabularDistribution( ){ return { *this }; }
  // LAW=5
  GeneralEvaporationSpectrum::Builder< Builder >
  generalEvaporationSpectrum( ){ return { *this }; }
  // LAW=7
  SimpleMaxwellianFissionSpectrum::Builder< Builder >
  simpleMaxwellianFissionSpectrum( ){ return { *this }; }
  // LAW=9
  SimpleMaxwellianFissionSpectrum::Builder< Builder >
  evaporationSpectrum( ){ return { *this }; }
  // LAW=11
  EnergyDependentWattSpectrum::Builder< Builder >
  energyDependentWattSpectrum( ){ return { *this }; }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/energies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/probabilities.hpp"

};
