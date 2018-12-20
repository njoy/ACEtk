template< typename DerivedBuilder, typename ParentBuilder >
class Builder: 
  public ContinuousEnergyNeutron::Builder::Tabulated1D::Builder< 
    Builder< DerivedBuilder, ParentBuilder > > {

public:
  using BaseBuilder = ContinuousEnergyNeutron::Builder::Tabulated1D::Builder< 
    Builder< DerivedBuilder, ParentBuilder > >;

protected:
  std::reference_wrapper< ParentBuilder > parent;


public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

};
