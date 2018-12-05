FissionMultiplicity::Builder fissionMultiplicity( std::string nuType ) { 
  if( not ( ( nuType == "total" ) or 
           ( nuType == "prompt" ) or 
           ( nuType == "delayed" ) ) ){
    Log::error( "Invalid type of fission multiplicity: {}", nuType );
    Log::info( "Valid fission multiplicity types are: "
              "total, prompt, or delayed" );
    throw std::range_error( "invalid fission multiplicity type" );
  }
  return FissionMultiplicity::Builder{ *this, nuType }; 
}
