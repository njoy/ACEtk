DiscretePhotonEnergy construct(){
  try {
    return { primaryFlag_.value(), energy_.value() };
  } catch( std::bad_optional_access& e ) {
    Log::info( "Some component of DiscretePhotonEnergy not built." );
    throw;
  }
}
