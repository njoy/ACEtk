template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cdf( Range&& cdf ){
  try {
    this->cdf_ = std::move( details::verify::cdf( cdf ) );
  } catch( details::verify::exceptions::InvalidCDF& ){
    Log::info( "Invalid CDF in Kalbach-Mann Angular Distribution Data." );
    throw;
  }
  return *this;
}
