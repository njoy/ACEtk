class Builder{
  using ParentBuilder = PhotonProduction::Builder;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< dvP< 
      dvS< std::vector< double > > > > energyGrid_;
  std::optional< std::vector<
    dvP< std::array< double, 33 > > > > cosineBins_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/AngularDistribution/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addAngularDistribution( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/AngularDistribution/Builder/src/cosineBins.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/AngularDistribution/Builder/src/energyGrid.hpp"

};