template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& values( Range&& xs ){
  try{
    this->values_ = std::move( details::verify::positive( xs ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "Cross section values must be all positive" );
    throw;
  }
}
