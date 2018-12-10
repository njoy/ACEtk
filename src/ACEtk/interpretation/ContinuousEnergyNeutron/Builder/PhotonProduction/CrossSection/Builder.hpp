class Builder:
  public ContinuousEnergyNeutron::Builder::CrossSection::Builder< 
    Builder, ParentBuilder > {

  using BaseBuilder = ContinuousEnergyNeutron::Builder::
    CrossSection::Builder< Builder, ParentBuilder >;

  int MT;
  std::optional< 
      details::verify::Positive< std::vector< double > > > values_;
  std::optional< Table::Slice > energyGrid_;

protected:

public:
  Builder( ParentBuilder& parent, int MT ):
    BaseBuilder( parent ),
    MT( MT )
  { }

  ParentBuilder& add(){
    return parent.get().addPhotonProduction( this->MT, this->construct() );
  }

  using BaseBuilder::energies;
  using BaseBuilder::values;
};
