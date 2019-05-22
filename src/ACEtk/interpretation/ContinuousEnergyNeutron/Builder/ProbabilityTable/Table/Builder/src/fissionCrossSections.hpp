template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& fissionCrossSections( Range&& fission ){
  try{
    this->fissionXS_ = std::make_optional< 
      dvP< std::vector< double > > >( 
        std::move( fission ) | ranges::to_vector );
    return *this;
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "Trouble adding fission cross section in probability table" );
    throw;
  }
}

