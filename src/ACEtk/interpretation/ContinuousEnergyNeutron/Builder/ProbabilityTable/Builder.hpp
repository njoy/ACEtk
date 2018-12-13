class Builder{
private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;

  std::optional< int > interpolationParameter_;
  std::optional< int > inelasticCompetition_;
  std::optional< int > otherAbsorption_;
  std::optional< Factors > factors_;
  std::optional< details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > > incidentEnergies_;
  std::optional< details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > > CDFs_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/construct.hpp"

public:
  Builder( ContinuousEnergyNeutron::Builder& parent ):
    parent( parent )
  { }

  // ContinuousEnergyNeutron::Builder& add() { 
  //   return parent.get().addProbabilityTable( this->construct() );
  // }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/interpolationParameter.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/inelasticCompetition.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/otherAbsorption.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/factors.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/incidentEnergies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/CDFs.hpp"
};
