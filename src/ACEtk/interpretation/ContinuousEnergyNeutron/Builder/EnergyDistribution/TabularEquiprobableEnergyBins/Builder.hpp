template< typename ParentBuilder >
class Builder: 
  public ContinuousEnergyNeutron::Builder::Tabulated1D::Builder< 
    Builder< ParentBuilder > > {

protected:
  std::reference_wrapper< ParentBuilder > parent;

public:
  Builder( EnergyDistribution::Builder< ParentBuilder >& parent ):
    parent( parent )
  { }

};
