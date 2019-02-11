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
  EnergyDistribution::TabularEquiprobableEnergyBins::Builder< Builder >
  tabularEquiprobableEnergyBins(){ return { *this }; }
  // LAW=2
  EnergyDistribution::DiscretePhotonEnergy::Builder< Builder >
  discretePhotonEnergy( ){ return { *this }; }
  // LAW=3
  EnergyDistribution::LevelScattering::Builder< Builder >
  levelScattering( ){ return { *this }; }
  // LAW=4
  EnergyDistribution::ContinuousTabularDistribution::Builder< Builder >
  continuousTabularDistribution( ){ return { *this }; }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/energies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/probabilities.hpp"

};
