ProbabilityTable construct(){
  try{
    details::verify::equalSize( this->CDFs_.value(), 
                                this->incidentEnergies_.value() );
  } catch( std::range_error& e){
    Log::info( "CDFs must be the same size as incident energies" );
    throw;
  }

  return ProbabilityTable{
    interpolationParameter_.value(),
    inelasticCompetition_.value(),
    otherAbsorption_.value(),
    factors_.value(),
    incidentEnergies_.value(),
    CDFs_.value()
  };
}

