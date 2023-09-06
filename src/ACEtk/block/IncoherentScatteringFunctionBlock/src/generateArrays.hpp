static std::vector< std::vector< double > > 
generateArrays( std::vector< double > values ) {

  if ( 21 != values.size() ) {

    Log::error( "The size of the XSS subrange in the JINC block for an "
                "mcplib style scattering function should be 21" );
    Log::info( "XSS.size(): {}", values.size() );
    throw std::exception();
  }
  return { std::move( values ) };
}
