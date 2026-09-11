template < typename Number >
static std::vector< double >
generateXSS( std::vector< std::vector< Number > >&& vals ) {

  std::vector< double > xss;
  const auto nrows = vals.size();
  const auto ncols = vals.front().size();
  const auto sz = nrows * ncols;
  xss.reserve( sz );

  for ( auto&& array: vals ) {

    if ( array.size() != ncols ) {

      Log::error( "The size of a rectangular matrix data array is not as expected in" );
      Log::info( "Expected: {} elements", ncols );
      Log::info( "Found: {} elements", array.size() );
      throw std::exception();
    }
    xss.insert( xss.end(), array.begin(), array.end() );
  }

  return xss;
}
