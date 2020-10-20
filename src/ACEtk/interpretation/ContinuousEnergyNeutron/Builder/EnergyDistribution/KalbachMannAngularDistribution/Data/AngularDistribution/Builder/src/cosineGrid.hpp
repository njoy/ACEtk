template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cosineGrid( Range&& cosines ){
  try {
    this->cosineGrid_ = std::move( details::verify::cosineBins( cosines ) );
  } catch( details::verify::exceptions::InvalidCosine& ){
    Log::info( "Invalid cosine grid in Kalbach-Mann Angular Distribution." );
    throw;
  }
  return *this;
}
