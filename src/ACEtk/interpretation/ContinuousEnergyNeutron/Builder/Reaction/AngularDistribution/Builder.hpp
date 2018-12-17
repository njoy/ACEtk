class Builder {
  using ParentBuilder = ContinuousEnergyNeutron::Builder::Reaction::Builder;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< details::verify::Positive< 
      details::verify::Sorted< std::vector< double > > > > energyGrid_;
  std::vector< Format > representations_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder/src/construct.hpp"

public: 
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  // ParentBuilder& add() {
  //   return parent.get().addAngularDistribution( this->construct() );
  // }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder/src/energyGrid.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder/src/isotropic.hpp"

  Equiprobable::Builder equiprobableCosineBins(){
    return Equiprobable::Builder{ *this };
  }
  // Tabulated::Builder tabulated(){
  //   return Tabulated::Builder{ *this };
  // }

};
