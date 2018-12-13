template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& fissionCrossSections( Range&& fission ){
  try{
    this->fissionXS_ = fission;
    return *this;
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "Trouble adding fission cross section in probability table" );
    throw;
  }
}

