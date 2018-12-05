class Builder{
private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;
  std::optional< std::vector< double > > crossSection_;
  std::optional< std::array< std::array< double, 20 >, 30 > > outgoingEnergies_;

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

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaproduction/Builder/src/crossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/TotalGammaproduction/Builder/src/outgoingEnergies.hpp"
};
