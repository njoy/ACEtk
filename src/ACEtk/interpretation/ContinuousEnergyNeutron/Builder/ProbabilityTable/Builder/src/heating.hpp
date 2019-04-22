template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& heating( Range&& heat ){
  try{
    this->heating_ = std::make_optional< 
      dvP< std::vector< double > > >( 
        std::move( heat ) | ranges::to_vector );
    return *this;
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "Trouble adding heating values in probability table" );
    throw;
  }
}
