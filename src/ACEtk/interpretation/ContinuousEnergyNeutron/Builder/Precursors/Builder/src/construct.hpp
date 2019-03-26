Precursors construct() {
  try{
    return Precursors{ 
      decayConstant_.value(), 
      TabBuilder::construct(),
      energyDistribution_.value()
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Some delayed Precursors component not built." );
    throw;
  }
}
