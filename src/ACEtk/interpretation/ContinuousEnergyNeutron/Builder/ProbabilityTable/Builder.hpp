class Builder{
private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;

  std::optional< int > interpolationParameter_;
  std::optional< int > inelasticCompetition_;
  std::optional< int > otherAbsorption_;
  std::optional< Factors > factors_;
  std::optional< dvP< 
    dvS< std::vector< double > > > > incidentEnergies_;
  std::optional< dvC< std::vector< double > > > CDFs_;
  std::optional< dvP< std::vector< double > > > totalXS_;
  std::optional< 
    dvP< std::vector< double > > > elasticXS_;
  std::optional< 
    dvP< std::vector< double > > > fissionXS_;
  std::optional< 
    dvP< std::vector< double > > > captureXS_;
  std::optional< 
    dvP< std::vector< double > > > heating_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/equalSize.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/construct.hpp"

public:
  Builder( ContinuousEnergyNeutron::Builder& parent ):
    parent( parent )
  { }

  ContinuousEnergyNeutron::Builder& add() { 
    return parent.get().addProbabilityTable( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/interpolationParameter.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/inelasticCompetition.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/otherAbsorption.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/factors.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/incidentEnergies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/CDFs.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/totalCrossSections.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/elasticCrossSections.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/fissionCrossSections.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/captureCrossSections.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/heating.hpp"
};
