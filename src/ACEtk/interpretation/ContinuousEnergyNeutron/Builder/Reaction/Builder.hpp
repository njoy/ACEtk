class Builder{

private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;
  int MT_;
  std::optional< int > neutronYield_;
  std::optional< NeutronYieldReferenceFrame > neutronYieldReferenceFrame_;
  std::optional< double > Q_;
  std::optional< ContinuousEnergyNeutron::Builder::CrossSection > crossSection_;
  std::optional< AngularDistribution > angularDistribution_;
  std::optional< EnergyDistribution > energyDistribution_;
  std::optional< Table::Slice > energyGrid_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addCrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addAngularDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addEnergyDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/construct.hpp"

  friend CrossSection::Builder;
  friend AngularDistribution::Builder;
  friend EnergyDistribution::Builder< Builder >;

public:
  Builder( ContinuousEnergyNeutron::Builder& parent, int MT ):
    parent( parent ), MT_( MT )
  { }

  ContinuousEnergyNeutron::Builder& add() { 
    return parent.get().addReaction( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/energyGrid.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/crossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/Q.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/neutronYield.hpp"
  AngularDistribution::Builder angularDistribution(){ 
    return AngularDistribution::Builder{ *this }; 
  }
  EnergyDistribution::Builder< Builder > energyDistribution(){ 
    return EnergyDistribution::Builder< Builder >{ *this }; 
  }
};
