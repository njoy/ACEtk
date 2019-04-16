class Builder{
public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/NeutronYieldReferenceFrame.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Factors.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable.hpp"

protected:
  std::optional< Table::Header > header_;
  std::optional< Table::Data > tableData_;

  std::optional< details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > > energyGrid_;

  std::optional< details::verify::Positive< std::vector< double > > > totalXS_;

  std::optional< details::verify::Positive< std::vector< double > > > 
      totalDisappearanceXS_;

  std::optional< 
      details::verify::Positive< std::vector< double > > > elasticXS_;

  std::optional< details::verify::Positive< std::vector< double > > > heating_;

  std::optional< int > SZA_;
  tsl::hopscotch_map< std::string, Nubar > fissionMultiplicity_;

  std::vector< Precursors > delayedPrecursors_;

  std::map< int, Reaction > reactions_;

  std::map< int, PhotonProductionReaction > photonProductionReactions_;

  std::optional< TotalGammaProduction > totalGammaProduction_;
  std::optional< ProbabilityTable > probabilityTable_;

  friend Reaction::Builder;
  friend PhotonProductionReaction::Builder;
  friend Table::Header::Builder< Builder >;
  friend Precursors::Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addHeader.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addFissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addTotalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addPhotonProductionReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addProbabilityTable.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addPrecursor.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/energyGrid.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/ACEifyEDs.hpp"
protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/ESZ.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/NU.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/MTR.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/LQR.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/TYR.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/SIG.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/AND.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/totalCrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/totalDisappearanceCrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/heating.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/SZA.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/fissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/totalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/photonProductionReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/precursors.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/reaction.hpp"

  ProbabilityTable::Builder probabilityTable(){ 
    return ProbabilityTable::Builder{ *this }; }

  Table::Header::Builder< Builder > header(){ 
    return Table::Header::Builder< Builder >{ *this }; }
};
