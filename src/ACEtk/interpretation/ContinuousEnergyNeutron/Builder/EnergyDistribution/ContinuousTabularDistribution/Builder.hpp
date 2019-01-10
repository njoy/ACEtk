template< typename ParentBuilder >
class Builder: 
  public ContinuousEnergyNeutron::Builder::Tabulated1D::Builder< 
    Builder< ParentBuilder > >,
  public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {

  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

protected:

public:
  using BaseBuilder::BaseBuilder;

};
