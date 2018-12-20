template< typename DerivedBuilder, typename DerivedType, typename ParentBuilder >
class Builder: 
  public Tabulated1D::Builder< Builder< DerivedBuilder, ParentBuilder > >{

  using BaseBuilder = ContinuousEnergyNeutron::Builder::
      Tabulated1D::Builder< Builder >;

protected:
  std::reference_wrapper< ParentBuilder > parent;

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  using BaseBuilder::boundaries;
  using BaseBuilder::schemes;

  TabularEquiprobableEnergyBins::Builder tabularEquiprobableEnergyBins(){
    return TabularEquiprobableEnergyBins::Builder { ... };
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
