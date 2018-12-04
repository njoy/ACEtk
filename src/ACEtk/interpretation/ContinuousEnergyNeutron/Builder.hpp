class Builder{
protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity.hpp"

  std::optional< std::vector< double > > energyGrid_;
  tsl::hopscotch_map< std::string, Nubar > fissionMultiplicity_;
  tsl::hopscotch_map< int, Reaction > reactions_;

  friend Reaction::Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addFissionMultiplicity.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/energyGrid.hpp"
  Reaction::Builder reaction( int MT ){ return Reaction::Builder{ MT, *this }; }

  FissionMultiplicity::Builder fissionMultiplicity( std::string nuType ) { 
    if( not ( ( nuType == "total" ) or 
            ( nuType == "prompt" ) or 
            ( nuType == "delayed" ) ) ){
      Log::error( "Invalid type of fission multiplicity: {}", nuType );
      Log::info( "Valid fission multiplicity types are: "
                "total, prompt, or delayed" );
      throw std::range_error( "invalid fission multiplicity type" );
    }
    return FissionMultiplicity::Builder{ *this, nuType }; 
  }

};
