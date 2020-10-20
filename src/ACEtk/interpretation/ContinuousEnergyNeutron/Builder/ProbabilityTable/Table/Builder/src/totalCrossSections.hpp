template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& totalCrossSections( Range&& total ){
  try{
    this->totalXS_ = std::move( details::verify::positive( total ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "Trouble adding total cross section in probability table" );
    throw;
  }
}

