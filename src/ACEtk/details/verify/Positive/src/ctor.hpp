template< typename... Args >
Positive( Args&&... args ):
  T( std::forward< Args >( args )... )
{
  auto firstNegative = ranges::find_if( *this, [](auto& e ){ return e < 0; } );

  if( firstNegative != this->end() ){
    njoy::Log::error( "All elements of the range must be positive" );
    njoy::Log::info( "First negative element ({}) found at index: {}",
                     *firstNegative, ( firstNegative - this->begin() ) );
    throw std::exception();
  }
}

Positive( Sorted< T >&& range ):
  T( std::forward< Sorted< T > >( range ) )
{
  if( *( this->begin() ) < 0.0 ){
    njoy::Log::error( "All elements of the range must be positive" );
    njoy::Log::info( "Negative element ({}) found at index: {}",
                     *(std::begin( range ) ), 0 );
    throw std::exception();
  }
}
