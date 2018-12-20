template< typename DerivedBuilder, typename DerivedType, typename ParentBuilder >
class Builder: 
  public Tabulated1D::Builder< 
    Builder< DerivedBuilder, DerivedType, ParentBuilder > >{

  using BaseBuilder = Tabulated1D::Builder< 
    Builder< DerivedBuilder, DerivedType, ParentBuilder > >;

protected:
  std::reference_wrapper< ParentBuilder > parent;
  using BaseBuilder::construct;

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  using BaseBuilder::boundaries;
  using BaseBuilder::schemes;

  typename DerivedType::TabularEquiprobableEnergyBins::Builder 
  tabularEquiprobableEnergyBins(){
    return { parent };
  }

#define RENAME(basename, derivedname)\
  template< typename Range,\
            utility::Require< true, utility::is_range, Range > = true >\
  Builder& derivedname( Range&& derivedname ){\
    return BaseBuilder::basename( std::move( derivedname ) );\
  }

  RENAME( x, energies )
  RENAME( y, probabilities )
#undef RENAME
};
