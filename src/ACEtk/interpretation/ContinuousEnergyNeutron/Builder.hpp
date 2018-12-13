class Builder{
public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/NeutronYieldReferenceFrame.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Factors.hpp"

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable.hpp"

  std::optional< details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > > energyGrid_;
  tsl::hopscotch_map< std::string, Nubar > fissionMultiplicity_;
  tsl::hopscotch_map< int, Reaction > reactions_;
  tsl::hopscotch_map< int, PhotonProductionReaction > photonProductionReactions_;
  std::optional< TotalGammaProduction > totalGammaProduction_;

  friend Reaction::Builder;
  friend PhotonProductionReaction::Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addFissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addTotalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addPhotonProductionReaction.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/energyGrid.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/fissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/totalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/photonProductionReaction.hpp"
  Reaction::Builder reaction( int MT ){ return Reaction::Builder{ *this, MT }; }
  ProbabilityTable::Builder probabilityTable(){ return ProbabilityTable::Builder{ *this }; }

};
