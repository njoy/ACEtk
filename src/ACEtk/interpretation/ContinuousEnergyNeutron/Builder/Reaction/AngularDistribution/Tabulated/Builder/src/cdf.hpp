template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cdf( Range&& cdf ){

  try{
    this->CDF_  = std::make_optional< 
      dvC< std::vector< double > > >( 
          std::move( cdf ) | ranges::to_vector 
      );
    return *this;
  } catch( details::verify::exceptions::InvalidCDF& e ){
    Log::info( "Trouble constructing CDF values in "
               "tabulated angular distribution" );
    throw;
  }
}
