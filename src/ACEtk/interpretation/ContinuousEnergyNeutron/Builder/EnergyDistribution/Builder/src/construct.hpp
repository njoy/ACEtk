EnergyDistribution construct(){
  try{
    return { BaseBuilder::construct(), law_.value() };
  } catch( std::bad_optional_access& e ){
    Log::error( "Energy distribution law must be specified" );
    throw;
  }
}
