EnergyDistribution construct(){
  if( not law_ ){
    Log::error( 
        "Energy distribution law must be specified before construction" );
    throw std::bad_optional_access();
  }
  try{
    return { BaseBuilder::construct(), law_.value() };
  } catch( std::bad_optional_access& e ){
    Log::error( "Some component of EnergyDistribution not specified" );
    throw;
  }
}
