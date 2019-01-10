class Builder{
private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;
  std::optional< std::vector< double > > crossSection_;
  std::optional< std::array<
    details::verify::Positive< 
      std::array< double, 20 > >, 30 > > outgoingEnergies_;

protected:
  TotalGammaProduction construct(){
    return TotalGammaProduction{
      std::move( crossSection_.value() ),
      std::move( outgoingEnergies_.value() )
    };
  }

public:
  Builder( ContinuousEnergyNeutron::Builder& parent ):
    parent( parent )
  { }

  ContinuousEnergyNeutron::Builder& add() { 
    return parent.get().addTotalGammaProduction( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction/Builder/src/crossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaProduction/Builder/src/outgoingEnergies.hpp"
};
