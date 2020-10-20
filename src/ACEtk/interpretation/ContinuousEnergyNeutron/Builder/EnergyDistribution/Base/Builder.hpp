template< typename Derived, typename ParentBuilder >
class Builder{

protected:
  std::reference_wrapper< ParentBuilder > parent;

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add(){
    return parent.get().addEnergyDistribution( 
      static_cast< Derived* >( this )->construct() );
  }
};
