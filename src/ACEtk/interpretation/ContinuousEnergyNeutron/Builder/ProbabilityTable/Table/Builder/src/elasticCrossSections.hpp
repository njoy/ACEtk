template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& elasticCrossSections( Range&& elastic ){
  try{
    this->elasticXS_ = std::make_optional< 
      dvP< std::vector< double > > >( 
        std::move( elastic ) | ranges::to_vector );
    return *this;
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "Trouble adding elastic cross section in probability table" );
    throw;
  }
}

