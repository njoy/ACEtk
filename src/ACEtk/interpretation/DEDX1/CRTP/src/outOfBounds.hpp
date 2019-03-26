static bool outOfBounds(TempT value, TempT min, TempT max) {
  const bool inbounds = ( min <= value ) and ( value <= max );
  if ( not inbounds ){    
    njoy::Log::error( "Could not find temperature in range" );
    njoy::Log::info( "The temperature in question is {}", value);
    njoy::Log::info( "The temperature range is ({},{})", min, max);                  
    throw std::domain_error("Could not find temperature in range");
  }  
  return not inbounds;
}

static bool outOfBounds(DenT value, DenT min, DenT max) {
  const bool inbounds = ( min <= value ) and ( value <= max );
  if ( not inbounds ){    
    njoy::Log::error( "Could not find density in range" );
    njoy::Log::info( "The density in question is {}", value);
    njoy::Log::info( "The density range is ({},{})", min, max);                  
    throw std::domain_error("Could not find density in range");
  }  
  return not inbounds;
}  

