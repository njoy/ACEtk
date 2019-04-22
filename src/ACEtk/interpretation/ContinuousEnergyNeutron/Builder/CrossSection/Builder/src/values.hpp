template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& values( Range&& xs ){
  try{
    this->values_ = std::make_optional< dvP< Range > >( 
      std::move( xs ) | ranges::to_vector );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "Cross section values must be all positive" );
    throw;
  }
}
