class Builder{
  using ParentBuilder = 
      ContinuousEnergyNeutron::Builder::PhotonProductionReaction::Builder;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< 
    details::verify::Positive< std::vector< double > > > energyGrid_;
  std::optional< std::vector<
    details::verify::Positive< std::array< double, 33 > > > > cosineBins_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addAngularDistribution( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution/Builder/src/cosineBins.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution/Builder/src/energyGrid.hpp"

};
