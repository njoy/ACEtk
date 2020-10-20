Precursors construct() {
  try{
    return Precursors{ 
      std::move( decayConstant_.value() ),
      TabBuilder::construct(),
      std::move( energyDistribution_ )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Some delayed Precursors component not built." );
    throw;
  }
}
