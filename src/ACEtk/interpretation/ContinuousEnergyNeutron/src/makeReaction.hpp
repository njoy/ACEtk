static
Reaction makeReaction( const Table& ACETable, int MT){

  int index;
  try{
    index = reactionIndex( neutronReactionIDs( ACETable ), MT );
  } catch( const std::exception& e ){
    njoy::Log::info( 
        "Can't make a Reaction because the identifier ({}) can't be found.", 
        MT );
    throw;
  }
  auto XS = makeCrossSection( ACETable, index );

  return Reaction( std::move( XS ) );
}

Reaction makeReaction( int MT ) const {
  return makeReaction( this->table, MT );
}
