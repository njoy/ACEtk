template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cosineBins( Range&& bins ){
  try{ 
    this->cosineBins_ = std::move( 
        details::verify::CosineBins< std::array< double, 33 > >( 
            details::make_array< 33 > (bins ) ) );

    auto values = cosineBins_.value();
    if( ( std::abs( values.front() ) > 1.0 ) or
        ( std::abs( values.back() )  > 1.0 ) ) {
      Log::error( "cosine values are invalid" );
      Log::info( "cosine values must be in [ -1.0, 1.0 ] " );
      throw std::range_error( "invalid cosine value(s)");
    }
    return *this;
  } catch( details::verify::exceptions::Unsorted& u ){
    Log::info( "equiprobable cosine bins must be sorted" );
    throw;
  }
}
