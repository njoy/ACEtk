class Builder:
  public ContinuousEnergyNeutron::Builder::CrossSection::Builder< 
      Builder, 
      ContinuousEnergyNeutron::Builder::Reaction::Builder
    > {

  using ParentBuilder = ContinuousEnergyNeutron::Builder::Reaction::Builder;
  using BaseBuilder = ContinuousEnergyNeutron::Builder::
    CrossSection::Builder< Builder, ParentBuilder >;
  std::optional< details::verify::Positive< std::vector< double > > > values_;
  std::optional< Table::Slice > energyGrid_;

public:
  Builder( ParentBuilder& parent ):
    BaseBuilder( parent )
  { }

  ParentBuilder& add(){
    return parent.get().addCrossSection( this->construct() );
  }

  using BaseBuilder::energyGrid;
  using BaseBuilder::values;
};
