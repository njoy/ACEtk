static std::vector< std::vector< double > > 
generateArrays( std::vector< double > integrated, std::vector< double > factors ) {

  if ( 110 != integrated.size() + factors.size() ) {

    Log::error( "The size of the XSS subrange in the JINC block for an "
                "mcplib style form factors should be two times 55" );
    Log::info( "integrated form factors size(): {}", integrated.size() );
    Log::info( "form factors size(): {}", factors.size() );
    throw std::exception();
  }
  return { std::move( integrated ), std::move( factors ) };
}
