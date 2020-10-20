class Builder: public Tabulated1D::Builder< Builder >{

  using ParentBuilder = PhotonProduction::Builder;
  using BaseBuilder = Tabulated1D::Builder< Builder >;

  std::reference_wrapper< ParentBuilder > parent;
  int MF;
  int MT;

protected:

  using BaseBuilder::x;
  using BaseBuilder::y;

public:
  Builder( ParentBuilder& parent, int MF, int MT ):
    parent( parent ),
    MF( MF ),
    MT( MT )
  { }

  Yields construct(){ 

    return { this->MF, this->MT, BaseBuilder::construct() };
  }

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

