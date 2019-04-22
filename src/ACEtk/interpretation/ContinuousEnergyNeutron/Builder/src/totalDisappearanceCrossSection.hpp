template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& totalDisappearanceCrossSection( Range&& xs ){
  try{
    this->totalDisappearanceXS_  = std::make_optional< 
      dvP< std::vector< double > > >( std::move( xs ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( 
      "total disappearance cross section values must be all positive" );
    throw;
  }
}
