template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& crossSection( Range&& xs){
  try{
    this->crossSection_ = std::move( details::verify::positive( xs ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "crossSection must be all positive" );
    throw;
  }
}
