EnergyDistribution construct(){
  try{
    return { BaseBuilder::construct(), law_.value() };
  } catch( std::bad_optional_access& e ){
    Log::error( "Some component of EnergyDistribution not specified" );
    throw;
  }
}
