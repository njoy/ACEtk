template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& pdf( Range&& pdf ){
  try {
    this->pdf_ = std::move( details::verify::pdf( pdf ) );
  } catch( details::verify::exceptions::InvalidCDF& ){
    Log::info( "Invalid PDF in Kalbach-Mann (LAW=44) Data." );
    throw;
  }
  return *this;
}
