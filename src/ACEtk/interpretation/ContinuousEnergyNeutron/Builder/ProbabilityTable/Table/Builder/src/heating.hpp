template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& heating( Range&& heat ){
  try{
    this->heating_ = std::move( details::verify::positive( heat ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "Trouble adding heating values in probability table" );
    throw;
  }
}
