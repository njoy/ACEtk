class Builder {

  using ParentBuilder = ContinuousEnergyNeutron::Builder::Reaction::
      AngularDistribution::Builder;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< 
    dvCB< std::array< double, 33 > > > cosineBins_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addEquiprobable( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable/Builder/src/values.hpp"
};
