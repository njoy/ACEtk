class UnresolvedResonanceRange {

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/UnresolvedResonanceRange/ProbabilityTable.hpp"

private:
  auto pTableColumn( int col ) const {
    return ranges::for_each( 
        probabilityTables_, [&]( auto& pT ){ return pT.parameter( col ); } );

    // return probabilityTables_
    //   | ranges::view::drop_exactly( col )
    //   | ranges::view::stride ( 6 );
  }
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/UnresolvedResonanceRange/src/makeProbabilityTables.hpp"

protected:
  int interpolationParameter_;
  int inelasticCompetition_;
  int otherAbsorption_;
  int factors_;
  Slice incidentEnergies_;
  std::vector< ProbabilityTable > probabilityTables_;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/UnresolvedResonanceRange/src/ctor.hpp"

  auto INTT() const{ return interpolationParameter_; }
  auto interpolationParameter() const{ return interpolationParameter_; }

  auto ILF() const{ return inelasticCompetition_; }
  auto inelasticCompetition() const{ return inelasticCompetition_; }

  auto IOA() const{ return otherAbsorption_; }
  auto otherAbsorption() const{ return otherAbsorption_; }

  auto IFF() const{ return factors_; }
  auto factors() const{ return factors_; }

  auto incidentEnergies() const{ return incidentEnergies_; }

  auto probabilityTables() const{ 
    return probabilityTables_
      | ranges::view::stride( incidentEnergies_.size() );
  }

  auto CDF() const       { return pTableColumn( 1 ); }
  auto totalXS() const   { return pTableColumn( 2 ); }
  auto elasticXS() const { return pTableColumn( 3 ); }
  auto fissionXS() const { return pTableColumn( 4 ); }
  auto captureXS() const { return pTableColumn( 5 ); }
  auto heating() const   { return pTableColumn( 6 ); }
};
