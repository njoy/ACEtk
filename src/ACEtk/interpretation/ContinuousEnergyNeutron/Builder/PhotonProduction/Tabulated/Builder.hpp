class Builder: 
  public ContinuousEnergyNeutron::Builder::Tabulated1D::Builder< Builder >{

  using BaseBuilder = ContinuousEnergyNeutron::Builder::
      Tabulated1D::Builder< Builder >;

  std::reference_wrapper< ParentBuilder > parent;
  int MT;

protected:

  using BaseBuilder::x;
  using BaseBuilder::y;

public:
  Builder( ParentBuilder& parent, int MT ):
    parent( parent ),
    MT( MT )
  { }

  ParentBuilder& add(){
    return parent.get().addPhotonProduction( this->MT, this->construct() );
  }

  using BaseBuilder::boundaries;
  using BaseBuilder::schemes;

#define RENAME(basename, derivedname)\
  Builder& derivedname( std::vector< double>&& derivedname ){\
    return BaseBuilder::basename( std::move( derivedname ) );\
  }

  RENAME( x, energies );
  RENAME( y, yields );
#undef RENAME
};

