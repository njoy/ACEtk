std::vector< ProbabilityTable > 
makeProbabilityTables( Slice pTables ){

  return pTables
    | ranges::view::chunk( 6 )
    | ranges::view::transform(
        [ ]( const auto& values ){ 
          return ProbabilityTable{ 
            Table::Slice{ values.begin(), values.end() } 
          }; 
        } 
    );
}
