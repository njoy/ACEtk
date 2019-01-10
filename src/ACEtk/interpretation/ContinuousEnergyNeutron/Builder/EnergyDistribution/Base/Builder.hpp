template< typename Derived, typename ParentBuilder >
class Builder {

protected:
  double energy_;
  double probability_;
  std::reference_wrapper< ParentBuilder > parent;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Base/Builder/src/checkEnergy.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Base/Builder/src/checkProbability.hpp"

public:
  Builder( double energy, double probability, ParentBuilder& parent ):
    energy_( checkEnergy( energy ) ),
    probability_( checkProbability( probability ) ),
    parent( parent )
  { }

  ParentBuilder& add(){
    return parent.get().addEnergyDistribution( 
      energy_, probability_,
      static_cast< Derived* >( this )->construct() );
  }

};
