class Builder{
public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/NeutronYieldReferenceFrame.hpp"

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity.hpp"

  std::optional< details::verify::Positive< std::vector< double > > > energyGrid_;
  tsl::hopscotch_map< std::string, Nubar > fissionMultiplicity_;
  tsl::hopscotch_map< int, Reaction > reactions_;
  std::optional< TotalGammaProduction > totalGammaProduction_;

  friend Reaction::Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addFissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addTotalGammaProduction.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/energyGrid.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/fissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/totalGammaProduction.hpp"
  Reaction::Builder reaction( int MT ){ return Reaction::Builder{ MT, *this }; }


};
