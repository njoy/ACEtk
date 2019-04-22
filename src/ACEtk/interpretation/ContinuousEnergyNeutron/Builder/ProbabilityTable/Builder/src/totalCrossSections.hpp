template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& totalCrossSections( Range&& total ){
  try{
    this->totalXS_ = std::make_optional< 
      dvP< std::vector< double > > >( 
        std::move( total ) | ranges::to_vector );
    return *this;
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "Trouble adding total cross section in probability table" );
    throw;
  }
}

