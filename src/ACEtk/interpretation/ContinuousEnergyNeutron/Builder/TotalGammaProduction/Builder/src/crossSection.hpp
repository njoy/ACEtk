Builder& crossSection( std::vector< double >&& xs){
  try{
    this->crossSection_ = std::move( details::verify::positive( xs ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "crossSection must be all positive" );
    throw;
  }
}
