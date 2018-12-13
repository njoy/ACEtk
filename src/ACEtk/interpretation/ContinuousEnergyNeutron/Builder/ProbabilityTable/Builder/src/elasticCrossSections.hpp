template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& elasticCrossSections( Range&& elastic ){
  try{
    this->elasticXS_ = elastic;
    return *this;
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "Trouble adding elastic cross section in probability table" );
    throw;
  }
}

