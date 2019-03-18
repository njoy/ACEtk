class Builder: public Tabulated1D::Builder< Builder >{

  using BaseBuilder = Tabulated1D::Builder< Builder >;

  std::reference_wrapper< ParentBuilder > parent;
  std::string nuType;

protected:

  using BaseBuilder::x;
  using BaseBuilder::y;

public:
  Builder( ParentBuilder& parent, std::string nuType ): 
    parent( parent ),
    nuType( nuType )
  { }

  ParentBuilder& add(){
    return parent.get().addFissionMultiplicity( this->nuType,  
                                                this->construct() );
  }

  using BaseBuilder::energies;

#define RENAME(basename, derivedname)\
  template< typename Range,\
            utility::Require< true, utility::is_range, Range > = true >\
  Builder& derivedname( Range&& derivedname ){\
    return BaseBuilder::basename( std::move( derivedname ) );\
  }

  RENAME( y, multiplicities )
  RENAME( y, nubar )
#undef RENAME
};
