template< typename T >
static void
verifyIndex( const T& sequence, const std::size_t index ) {
  if ( ( index < 1 ) || ( index > sequence.size() ) ){
    Log::error( "Illegal index argument" );
    Log::info( "Index value: {}", index );
    Log::info( "{} may be indexed with values between 1 and {} inclusively",
               Data::name( sequence ), sequence.size() );
    throw std::out_of_range( name( sequence ) );
  }
}
