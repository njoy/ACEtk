class Builder{

private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;
  int MT_;
  std::optional< int > neutronYield_;
  std::optional< NeutronYieldReferenceFrame > neutronYieldReferenceFrame_;
  std::optional< double > Q_;
  std::optional< CrossSection > crossSection_;
  std::variant< 
    std::monostate,
    Isotropic,
    AngularDistribution > angularDistribution_;
  std::vector< EnergyDistribution > energyDistribution_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addCrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addAngularDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addEnergyDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/constructNeutronProducing.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/constructNonNeutronProducing.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/isNeutronProducing.hpp"

  friend CrossSection::Builder< Builder >;
  friend AngularDistribution::Builder;
  friend EnergyDistribution::Builder< Builder >;

public:
  Builder( ContinuousEnergyNeutron::Builder& parent, int MT ):
    parent( parent ), MT_( MT )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/add.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/crossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/Q.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/neutronYield.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/angularDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/isotropic.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/energyDistribution.hpp"
};
