class Builder{
public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/NeutronYieldReferenceFrame.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Factors.hpp"

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable.hpp"

  std::optional< Table::Header > header_;

  std::optional< details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > > energyGrid_;
  std::optional< details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > > heating_;
  tsl::hopscotch_map< std::string, Nubar > fissionMultiplicity_;
  tsl::hopscotch_map< int, Reaction > reactions_;
  tsl::hopscotch_map< int, PhotonProductionReaction > photonProductionReactions_;
  std::optional< TotalGammaProduction > totalGammaProduction_;
  std::optional< ProbabilityTable > probabilityTable_;

  friend Reaction::Builder;
  friend PhotonProductionReaction::Builder;
  friend Table::Header::Builder< Builder >;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addHeader.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addFissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addTotalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addPhotonProductionReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addProbabilityTable.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/energyGrid.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/heating.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/fissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/totalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/photonProductionReaction.hpp"
  Reaction::Builder reaction( int MT ){ return Reaction::Builder{ *this, MT }; }
  ProbabilityTable::Builder probabilityTable(){ 
    return ProbabilityTable::Builder{ *this }; }

  Table::Header::Builder< Builder > header(){ 
    return Table::Header::Builder< Builder >{ *this }; }
};
