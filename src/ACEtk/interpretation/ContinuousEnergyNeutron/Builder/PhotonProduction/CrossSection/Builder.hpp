class Builder{

  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  using BaseBuilder = ParentBuilder::Tabulated1D::Builder< Builder >;

  std::reference_wrapper< ParentBuilder > parent;
  int MT;
  std::optional< 
      details::verify::Positive< std::vector< double > > > values_;
  std::optional< Table::Slice > energyGrid_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/CrossSection/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent, int MT ):
    parent( parent ),
    MT( MT )
  { }

  ParentBuilder& add(){
    return parent.get().addPhotonProduction( this->MT, this->construct() );
  }
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/CrossSection/Builder/src/values.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/CrossSection/Builder/src/energies.hpp"
};
