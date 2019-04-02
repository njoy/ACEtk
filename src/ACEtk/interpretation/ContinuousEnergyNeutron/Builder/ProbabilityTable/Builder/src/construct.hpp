ProbabilityTable construct(){

  equalSize( this->CDFs_, "CDF" );
  equalSize( this->totalXS_, "total cross section" );
  equalSize( this->elasticXS_, "elastic cross section" );
  if( this->fissionXS_ ){
    equalSize( this->fissionXS_, "fission cross section" );
  }
  else{
    this->fissionXS_ = ranges::view::repeat_n( 
        0.0, this->incidentEnergies_.value().size() ) | ranges::to_vector;
  }
  equalSize( this->captureXS_, "capture cross section" );
  if( this->heating_ ){
    equalSize( this->heating_, "heating" );
  }
  else{
    this->heating_ = ranges::view::repeat_n( 
        0.0, this->incidentEnergies_.value().size() ) | ranges::to_vector;
  }

  return ProbabilityTable{
    interpolationParameter_.value(),
    inelasticCompetition_.value(),
    otherAbsorption_.value(),
    factors_.value(),
    incidentEnergies_.value(),
    CDFs_.value(),
    totalXS_.value(),
    elasticXS_.value(),
    fissionXS_.value(),
    captureXS_.value(),
    heating_.value()
  };
}

