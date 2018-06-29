auto range(){
  std::vector< std::pair< int, std::pair< int, int > > > r;

  size_t i = 0;
  r.push_back( std::make_pair( schemes_[i], std::make_pair( 0, NBT_[ i ] ) ) );
  for( size_t i = 1; i < NBT_.size(); i++ ){
    r.push_back( std::make_pair( 
        schemes_[ i ], std::make_pair( NBT_[ i-1 ], NBT_[ i ] ) ) );
  }

  return r;
}
