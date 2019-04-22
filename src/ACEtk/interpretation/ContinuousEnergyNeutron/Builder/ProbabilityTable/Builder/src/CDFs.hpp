template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& CDFs( Range&& cdfs ){
  try{
    if( cdfs.back() != 1.0 ){
      Log::error( "Invalid final CDF value: {}", cdfs.back() );
      Log::info( "Final CDF value must be 1.0" );
      throw std::exception();
    }
    this->CDFs_ = std::make_optional< 
      dvC< std::vector< double > > >( 
        std::move( cdfs ) | ranges::to_vector );
    return *this;
  } catch( details::verify::exceptions::InvalidCDF& e ){
    Log::info( "Trouble constructing CDF values in probability table" );
    throw;
  }
}
