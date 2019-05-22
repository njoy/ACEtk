class Builder{
private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;

  std::optional< int > interpolationParameter_;
  std::optional< int > inelasticCompetition_;
  std::optional< int > otherAbsorption_;
  std::optional< Factors > factors_;
  std::optional< dvP< dvS< std::vector< double > > > > incidentEnergies_;
  std::vector< Table > tables_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/addTable.hpp"

  friend Table::Builder;

public:
  Builder( ContinuousEnergyNeutron::Builder& parent ):
    parent( parent )
  { }

  ContinuousEnergyNeutron::Builder& add() { 
    return parent.get().addProbabilityTable( this->construct() );
  }

  Table::Builder table(){
    return { *this };
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/interpolationParameter.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/inelasticCompetition.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/otherAbsorption.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/factors.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder/src/incidentEnergies.hpp"
};
