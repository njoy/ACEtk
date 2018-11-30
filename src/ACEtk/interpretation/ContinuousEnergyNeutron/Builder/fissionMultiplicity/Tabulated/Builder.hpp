class Builder: 
  public ContinuousEnergyNeutron::Builder::Tabulated1D::Builder< Builder >{

  using BaseBuilder = ContinuousEnergyNeutron::Builder::
      Tabulated1D::Builder< Builder >;

  std::reference_wrapper< ParentBuilder > parent;

protected:

  using BaseBuilder::x;
  using BaseBuilder::y;

public:
  Builder( ContinuousEnergyNeutron::Builder& parent ):
    parent( parent )
  { }

  ParentBuilder& add(){
    parent.get().addFissionMultiplicity( this->construct() );
    return parent;
  }

#define RENAME(basename, derivedname)\
  Builder& derivedname( std::vector< double>&& derivedname ){\
    return BaseBuilder::basename( std::move( derivedname ) );\
  }

  RENAME( x, energies );
  RENAME( y, multiplicities );
  RENAME( y, nubar );
#undef RENAME
};

