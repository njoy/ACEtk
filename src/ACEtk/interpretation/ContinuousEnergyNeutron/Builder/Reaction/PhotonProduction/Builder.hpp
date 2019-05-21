class Builder {
private:

  using ParentBuilder = Reaction::Builder;
  std::reference_wrapper< ParentBuilder > parent;
  int MF;
  int MT;

  std::optional< MFType > crossSection_;
  std::optional< AngularDistribution > angularDistribution_;
  std::vector< EnergyDistribution > energyDistribution_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/Builder/src/addCrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/Builder/src/addYields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/Builder/src/addAngularDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/Builder/src/addEnergyDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/Builder/src/construct.hpp"

  friend ContinuousEnergyNeutron::Builder::CrossSection::Builder< Builder >;
  friend Yields::Builder;
  friend AngularDistribution::Builder;
  friend EnergyDistribution::Builder< Builder >;

public:
  Builder( ParentBuilder& parent, int MF, int MT ):
    parent( parent ),
    MF( MF ),
    MT( MT )
  { }

  ParentBuilder& add(){
    return parent.get().addPhotonProduction( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/Builder/src/yields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/Builder/src/crossSection.hpp"

  AngularDistribution::Builder angularDistribution(){ 
    return AngularDistribution::Builder{ *this }; 
  }
  EnergyDistribution::Builder< Builder > energyDistribution(){ 
    return EnergyDistribution::Builder< Builder >{ *this }; 
  }
};
