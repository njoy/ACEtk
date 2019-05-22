ProbabilityTable construct(){
  try{
    for( decltype( auto ) table : this->tables_ ){
      details::verify::equalSize( this->incidentEnergies_.value(), table.CDFs );
    }
  } catch( std::range_error& e){
    Log::info( "There must be the same number of incident energies as "
               "CDF values in each of the probability tables." );
    throw;
  }

  return ProbabilityTable{
    std::move( interpolationParameter_.value() ),
    std::move( inelasticCompetition_.value() ),
    std::move( otherAbsorption_.value() ),
    std::move( factors_.value() ),
    std::move( incidentEnergies_.value() ),
    std::move( tables_ )
  };
}

