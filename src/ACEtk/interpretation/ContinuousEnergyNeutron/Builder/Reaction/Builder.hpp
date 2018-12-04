class Builder{

private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;
  int MT_;
  std::optional< int > neutronYield_;
  std::optional< NeutronYieldReferenceFrame > neutronYieldReferenceFrame_;
  std::optional< double > Q_;
  std::optional< std::vector< double > > crossSection_;
  std::optional< Table::Slice > energyGrid_;

protected:
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
  Builder( int MT, ContinuousEnergyNeutron::Builder& parent ):
    parent( parent ), MT_( MT ), neutronYield_( 0 )
  { }

  ContinuousEnergyNeutron::Builder& add() { 
    return parent.get().addReaction( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/crossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/Q.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/neutronYield.hpp"
};
