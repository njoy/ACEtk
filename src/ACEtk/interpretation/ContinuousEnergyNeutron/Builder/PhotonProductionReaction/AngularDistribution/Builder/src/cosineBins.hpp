template< typename Ror >
Builder& cosineBins( Ror&& bins ){

  auto toPositive = []( auto&& r ){
    return details::verify::positive( std::forward< decltype( r ) >( r ) );
  };

  try{
    this->cosineBins_ = bins
      | ranges::view::transform(
          hana::compose( toPositive, details::make_array< 33 > ) 
        )
      | ranges::to_vector;
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "cosine bins must be all positive" );
    throw;
  }
}
