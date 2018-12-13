template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& CDFs( Range&& cdfs ){
  try{
    if( cdfs.back() != 1.0 ){
      Log::error( "Invalid final CDF value: {}", cdfs.back() );
      Log::info( "Final CDF value must be 1.0" );
      throw std::exception();
    }
    this->CDFs_ = cdfs;
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "Probability table CDFs must be all positive" );
    throw;
  } catch( details::verify::exceptions::Unsorted& e ){
    Log::info( "Probability table CDFs must be sorted" );
    throw;
  }
}
