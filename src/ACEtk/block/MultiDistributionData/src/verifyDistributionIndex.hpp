void verifyDistributionIndex( const std::size_t index ) const {

  if ( ( index < 1 ) || ( index > this->numberDistributions() ) ) {

    Log::error( "Illegal distribution index argument into {} block",
                this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts a distribution index between 1 and {} inclusively",
               this->name(), this->numberDistributions() );
    throw std::out_of_range( this->name() );
  }
}
