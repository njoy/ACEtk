class Builder {
private:

  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  std::reference_wrapper< ParentBuilder > parent;
  int MF;
  int MT;

  std::optional< MFType > crossSection_;
  std::optional< AngularDistribution > angularDistribution_;
  std::optional< EnergyDistribution > energyDistribution_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addCrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addYields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addAngularDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addEnergyDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/construct.hpp"

  friend CrossSection::Builder< Builder >;
  friend Yields::Builder;
  friend AngularDistribution::Builder;
  friend EnergyDistribution::Builder< Builder >;

public:
  Builder( ParentBuilder& parent, int MF, int MT ):
    parent( parent ),
    MF( MF ),
    MT( MT )
  { }

  ContinuousEnergyNeutron::Builder& add(){
    return parent.get().addPhotonProductionReaction( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/yields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/crossSection.hpp"

  AngularDistribution::Builder angularDistribution(){ 
    return AngularDistribution::Builder{ *this }; 
  }
  EnergyDistribution::Builder< Builder > energyDistribution(){ 
    return EnergyDistribution::Builder< Builder >{ *this }; 
  }
};
