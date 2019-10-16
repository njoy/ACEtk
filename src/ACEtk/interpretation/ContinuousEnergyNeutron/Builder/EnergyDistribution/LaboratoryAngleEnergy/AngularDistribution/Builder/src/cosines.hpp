template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cosines( Range&& cosines ){
  try {
    this->cosines_ = std::move( details::verify::cosineBins( cosines ) );
  } catch( details::verify::exceptions::InvalidCosine& ){
    Log::info( "Trouble adding cosine bins in LAW=67 Angular distribution." );
    throw;
  }
  return *this;
}
