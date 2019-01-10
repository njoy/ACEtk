template< typename Derived, typename ParentBuilder >
class Builder {

protected:
  double probability_;
  std::reference_wrapper< ParentBuilder > parent;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Base/Builder/src/checkProbability.hpp"
public:
  Builder( double probability, ParentBuilder& parent ):
    probability_( checkProbability( probability ) ),
    parent( parent )
  { 
  }

  ParentBuilder& add(){
    return parent.get().addEnergyDistribution( 
        static_cast< Derived* >( this )->construct() );
  }

};
