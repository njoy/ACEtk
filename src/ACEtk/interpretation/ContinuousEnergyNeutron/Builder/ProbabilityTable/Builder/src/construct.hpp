ProbabilityTable construct(){
  try {
    details::verify::equalSize( 
      this->incidentEnergies_.value(), this->tables_ );

    return ProbabilityTable{
      std::move( interpolationParameter_.value() ),
      std::move( inelasticCompetition_.value() ),
      std::move( otherAbsorption_.value() ),
      std::move( factors_.value() ),
      std::move( incidentEnergies_.value() ),
      std::move( tables_ )
    };
  } catch( std::range_error& ){
    Log::info( "There must be the same number of tables as incident energies" );
    throw;
  } catch( std::bad_optional_access& ){
    Log::error( "Some component of ProbabilityTables not built." );
    throw;
  }
}

