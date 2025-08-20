template < typename Number >
static std::vector< double >
generateXSS( std::vector< Number >&& rows,
             std::vector< Number >&& cols,
             std::vector< std::vector< Number > >&& vals ) {
  
  std::vector< double > xss;
  const auto nrows = rows.size();
  const auto ncols = cols.size();
  const auto sz = nrows + ncols + nrows * ncols;
  xss.reserve( sz );
  
  bool rowmajor;
  if ( vals.front().size() == ncols ) {
    
    rowmajor = true;
    if (vals.size() != nrows ) {
      
      Log::error( "The size of the matrix data is not as expected" );
      Log::info( "Expected: {} arrays", nrows );
      Log::info( "Found: {} arrays", vals.size() );
      throw std::exception();
    }
  } else if ( vals.front().size() == nrows ) {
    
    rowmajor = false;
    if (vals.size() != ncols ) {
      
      Log::error( "The size of the matrix data is not as expected" );
      Log::info( "Expected: {} arrays", ncols );
      Log::info( "Found: {} arrays", vals.size() );
      throw std::exception();
    }
  } else {
    
    Log::error( "The size of the matrix data is not as expected" );
    Log::info( "Expected: {} or {}", nrows, ncols );
    Log::info( "Found: {}", vals.front().size() );
    throw std::exception();
  }
  
  xss.insert( xss.end(), rows.begin(), rows.end() );
  xss.insert( xss.end(), cols.begin(), cols.end() );
  for ( auto&& array: vals ) {
    
    if ( array.size() != vals.front().size() ) {
      
      Log::error( "The size of a matrix data array is not as expected" );
      Log::info( "Expected: {} elements", vals.front().size() );
      Log::info( "Found: {} elements", array.size() );
      throw std::exception();
    }
    xss.insert( xss.end(), array.begin(), array.end() );
  }
  
  return xss;
}
