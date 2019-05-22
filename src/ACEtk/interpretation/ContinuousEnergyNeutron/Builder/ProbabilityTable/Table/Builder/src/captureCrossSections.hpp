template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& captureCrossSections( Range&& capture ){
  try{
    this->captureXS_ = std::make_optional< 
      dvP< std::vector< double > > >( 
        std::move( capture ) | ranges::to_vector );
    return *this;
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "Trouble adding capture cross section in probability table" );
    throw;
  }
}


