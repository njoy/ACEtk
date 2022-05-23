void verifyIndices( const std::size_t incident, const std::size_t outgoing ) const {

  std::size_t max = this->NE();
  if ( ( incident < 1 ) || ( incident > max ) ) {

    Log::error( "Illegal incident energy index argument into the {} block", this->name() );
    Log::info( "Index value: {}", incident );
    Log::info( "{} accepts an index between 1 and {} inclusively",
               this->name(), max );
    throw std::out_of_range( this->name() );
  }

  max = this->IFENG() < 2 ? this->NIEB().value() : this->data_[ incident - 1 ].size();
  if ( ( outgoing < 1 ) || ( outgoing > max ) ) {

    Log::error( "Illegal outgoing energy index argument into the {} block", this->name() );
    Log::info( "Index value: {}", outgoing );
    Log::info( "{} accepts an index between 1 and {} inclusively",
               this->name(), max );
    throw std::out_of_range( this->name() );
  }
}
