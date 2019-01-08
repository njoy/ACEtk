template<  typename ParentBuilder >
class Builder {

  std::optional< std::vector< int > > boundaries_;
  std::optional< std::vector< int > > schemes_;
  std::optional< std::vector< double > > energies_;
  std::vector< double > probabilities_;
  std::vector< LAWS > laws_;

  template< typename Derived, typename PB >
  friend class Base::Builder;
  
protected:
  std::reference_wrapper< ParentBuilder > parent;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/addEnergyDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/construct.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/boundaries.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/schemes.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/energies.hpp"
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addEnergyDistribution( this->construct() );
  }

  EnergyDistribution::DiscretePhotonEnergy::Builder< Builder >
  discretePhotonEnergy( double probability ){
    return { probability, *this };
  }

};
