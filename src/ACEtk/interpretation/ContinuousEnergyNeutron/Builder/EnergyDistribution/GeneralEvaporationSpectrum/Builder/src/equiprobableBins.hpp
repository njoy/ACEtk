template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& equiprobableBins( Range&& bins ){
  try {
    this->equiprobableBins_ = details::verify::positive( bins );
  } catch( details::verify::exceptions::NotPositive& ){
    Log::info( "Equiprobable bins must be all positive." );
    throw;
  }
  return *this;
}
