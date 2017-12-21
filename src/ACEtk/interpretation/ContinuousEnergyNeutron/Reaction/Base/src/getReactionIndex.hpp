template< typename A >
static
int getReactionIndex( A MTs, int ID ){

  auto it = std::find( MTs.begin(), MTs.end(), ID );
  if( it != MTs.end() ){
    return std::distance( MTs.begin(), it );
  }
  else{
    njoy::Log::error( "Couldn't find reaction index" );
    njoy::Log::info( "Looking for reaction ID: {}", ID );
    throw std::exception();
  }
}
