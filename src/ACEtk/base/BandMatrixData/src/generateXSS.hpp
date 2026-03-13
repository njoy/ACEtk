static std::vector< double >
generateXSS( std::vector< std::vector< double > >&& vals,
            unsigned int nsuper, unsigned int nsub ) {

  std::vector< double > xss;
  unsigned int nrows = vals.size();
  unsigned int ncols = vals.front().size();

  if ( nrows != ncols ) {

    Log::error( "BandMatrixData requires a square matrix" );
    Log::info( "Matrix has {} rows", nrows );
    Log::info( "But the first row is length {} ", ncols);
    throw std::exception();
  }

  if ( nsuper >= nrows ) {
    
    Log::error( "Number of super-diagonals cannot be greater than or equal to the number of rows" );
    Log::info( "Number of rows: {} ", nrows );
    Log::info( "Number of super-diagonals: {} ", nsuper );
  }
  if ( nsub >= nrows ) {
    
    Log::error( "Number of sub-diagonals cannot be greater than or equal to the number of rows" );
    Log::info( "Number of rows: {} ", nrows );
    Log::info( "Number of sub-diagonals: {} ", nsub );
  }

  const auto sz = nrows * (1+nsub + nsuper) - ((nsub * (1+nsub)) + (nsuper * (1+nsuper))) / 2 ; 

  xss.reserve( sz );

  unsigned int k = 0;
  unsigned int rowStart;
  unsigned int rowEnd;

  for ( auto&& array: vals ) {

    k++;

    if ( array.size() != ncols ) {

      Log::error( "The size of the diagonal matrix data array is not as expected in row {}", k );
      Log::info( "Expected: {} elements", ncols );
      Log::info( "Found: {} elements", array.size() );
      throw std::exception();
    }

    // both of these calculations are based on one-indexed matrices
    rowStart = std::max( k - nsub, static_cast< unsigned int >( 1 ) );   
    rowEnd = std::min( nrows, k + nsuper );


    if ( array.begin() + rowEnd  > array.end() ) {
      Log::error( "The row end calculation is beyond the end of the array for row {}", k );
      Log::info( "Array length: {}", array.size() );
      Log::info( "Calculated row end: {} ", rowEnd );
      throw std::exception();
    }

    xss.insert( xss.end(), array.begin() + ( rowStart - 1 ), array.begin() + ( rowEnd ) );

  }

  return xss;
}
