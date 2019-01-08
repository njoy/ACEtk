template< typename Derived, typename ParentBuilder >
class Builder {

protected:
  double probability_;
  std::reference_wrapper< ParentBuilder > parent;

public:
  Builder( double probability, ParentBuilder& parent ):
    probability_( probability ),
    parent( parent )
  { }

  ParentBuilder& add(){
    return parent.get().addEnergyDistribution( 
        static_cast< Derived* >( this )->construct() );
  }

};
