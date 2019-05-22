class Builder{
private:
  using PBuilder = ContinuousEnergyNeutron::Builder::ProbabilityTable::Builder;
  std::reference_wrapper< PBuilder > parent;

  std::optional< dvC< std::vector< double > > > CDFs_;
  std::optional< dvP< std::vector< double > > > totalXS_;
  std::optional< dvP< std::vector< double > > > elasticXS_;
  std::optional< dvP< std::vector< double > > > fissionXS_;
  std::optional< dvP< std::vector< double > > > captureXS_;
  std::optional< dvP< std::vector< double > > > heating_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/Builder/src/equalSize.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/Builder/src/construct.hpp"

public:
  Builder( PBuilder& parent ):
    parent( parent )
  { }

  PBuilder& add() { 
    return parent.get().addTable( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/Builder/src/CDFs.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/Builder/src/totalCrossSections.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/Builder/src/elasticCrossSections.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/Builder/src/fissionCrossSections.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/Builder/src/captureCrossSections.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/Builder/src/heating.hpp"
};
