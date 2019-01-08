template< typename ParentBuilder >
class Builder: 
  public ContinuousEnergyNeutron::Builder::Tabulated1D::Builder< 
    Builder< ParentBuilder > > {

protected:
  std::reference_wrapper< ParentBuilder > parent;
  double probability_;

public:
  Builder( double probability, ParentBuilder& parent ):
    probability_( probability ),
    parent( parent )
  { }

};
