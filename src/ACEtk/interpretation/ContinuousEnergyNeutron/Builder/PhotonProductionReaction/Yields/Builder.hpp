class Builder: 
  public ContinuousEnergyNeutron::Builder::Tabulated1D::Builder< Builder >{

  using ParentBuilder = ContinuousEnergyNeutron::Builder::
      PhotonProductionReaction::Builder;
  using BaseBuilder = ContinuousEnergyNeutron::Builder::
      Tabulated1D::Builder< Builder >;

  std::reference_wrapper< ParentBuilder > parent;

protected:

  using BaseBuilder::x;
  using BaseBuilder::y;

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add(){
    return parent.get().addYields( this->construct() );
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
  RENAME( y, values )
#undef RENAME
};

