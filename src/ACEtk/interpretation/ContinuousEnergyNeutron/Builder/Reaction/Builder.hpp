class Builder{

private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;
  int MT_;
  std::optional< int > neutronYield_;
  std::optional< NeutronYieldReferenceFrame > neutronYieldReferenceFrame_;
  std::optional< double > Q_;
  std::optional< ContinuousEnergyNeutron::Builder::CrossSection > crossSection_;
  std::optional< Table::Slice > energyGrid_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/addCrossSection.hpp"

  friend CrossSection::Builder;
  Reaction construct(){
    return Reaction{ 
      MT_, 
      Q_.value(),
      neutronYield_.value_or( 0 )*
        static_cast< int >( neutronYieldReferenceFrame_.value_or( 
            NeutronYieldReferenceFrame::LAB ) ),
      energyGrid_.value(),
      std::move( this->crossSection_.value() ) };
  }

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
};
