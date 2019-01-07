template<  typename ParentBuilder >
class Builder: 
  public Tabulated1D::Builder< Builder< ParentBuilder > >{

  using BaseBuilder = Tabulated1D::Builder< Builder< ParentBuilder > >;

protected:
  std::reference_wrapper< ParentBuilder > parent;
  using BaseBuilder::construct;

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  // ParentBuilder& add() {
  //   return parent.get().addEnergyDistribution( 
  //     static_cast< EnergyDistribution& >( this->construct() ) );
  // }

  EnergyDistributions::TabularEquiprobableEnergyBins::Builder< Builder > 
  tabularEquiprobableEnergyBins( double probability ){
    return { probability, *this };
  }
  EnergyDistributions::ContinuousTabularDistribution::Builder< Builder > 
  continuousTabularDistribution( double probability ){
    return { probability, *this };
  }

  using BaseBuilder::boundaries;
  using BaseBuilder::schemes;
#define RENAME(basename, derivedname)\
  template< typename Range,\
            utility::Require< true, utility::is_range, Range > = true >\
  Builder& derivedname( Range&& derivedname ){\
    return BaseBuilder::basename( std::move( derivedname ) );\
  }

  RENAME( x, energies )
#undef RENAME
};
