template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cdf( Range&& cdf ){
  try {
    this->cdf_ = std::move( details::verify::cdf( cdf ) );
  } catch( details::verify::exceptions::InvalidCDF& ){
    Log::info( "Trouble adding CDF to LAW=67 angular/energy distribution." );
    Log::info( "Invalid CDF." );
    throw;
  }
  return *this;
}
