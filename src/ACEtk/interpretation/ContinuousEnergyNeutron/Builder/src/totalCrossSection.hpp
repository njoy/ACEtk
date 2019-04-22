template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& totalCrossSection( Range&& xs ){
  try{
    this->totalXS_ = std::make_optional< 
      dvP< std::vector< double > > >( std::move( xs ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "total cross section values must be all positive" );
    throw;
  }
}
