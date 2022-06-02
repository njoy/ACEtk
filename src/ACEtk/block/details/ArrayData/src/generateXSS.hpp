static std::vector< double >
generateXSS( std::vector< std::vector< double > >&& arrays ) {

  std::vector< double > xss;
  auto n = arrays.front().size();
  xss.reserve( arrays.size() * n );

  unsigned int index = 1;
  for ( auto&& array : arrays ) {

    if ( array.size() != n ) {

      Log::error( "The size of the array with index {} is not as expected", index );
      Log::info( "Expected: {}", n );
      Log::info( "Found: {}", array.size() );
      throw std::exception();
    }

    xss.insert( xss.end(), array.begin(), array.end() );
    index++;
  }

  return xss;
}
