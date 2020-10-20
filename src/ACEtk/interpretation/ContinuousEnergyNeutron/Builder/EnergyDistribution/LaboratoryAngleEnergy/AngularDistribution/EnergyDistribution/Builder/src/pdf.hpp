template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& pdf( Range&& pdf ){
  try {
    this->pdf_ = std::move( details::verify::pdf( pdf ) );
  } catch( details::verify::exceptions::InvalidPDF& ){
    Log::info( "Trouble adding PDF to LAW=67 angular/energy distribution." );
    Log::info( "Invalid PDF." );
    throw;
  }
  return *this;
}
