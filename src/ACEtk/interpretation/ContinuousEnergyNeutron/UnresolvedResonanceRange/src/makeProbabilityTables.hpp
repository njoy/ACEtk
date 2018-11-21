auto
makeProbabilityTables( Slice pTables ){

  return pTables
    | ranges::view::chunk( 6 )
    | ranges::view::transform(
        [ ]( auto values ){ 
          return ProbabilityTable{ Table::slice( values ) }; } )
    | ranges::to_vector;
}
