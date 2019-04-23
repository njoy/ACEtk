template< typename Range,
  utility::Require< true, std::is_constructible, dvPsvd, Range > = true
  >
Builder& values( Range&& xs ){
  try{
    this->values_ = dvPsvd{ std::forward< Range> ( xs ) };
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "Cross section values must be all positive" );
    throw;
  }
}

template< typename Range,
  utility::Require< false, std::is_constructible, dvPsvd, Range > = true,
  utility::Require< true, utility::is_range, Range > = true
  >
Builder& values( Range&& xs ){
  return this->values( xs | ranges::to_vector );
}
