template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& pdf( Range&& pdf ){
  try {
    this->pdf_ = std::move( details::verify::pdf( pdf ) );
  } catch( details::verify::exceptions::InvalidPDF& ){
    Log::info( "Invalid PDF in Kalbach-Mann Angular Distribution Data." );
    throw;
  }
  return *this;
}
