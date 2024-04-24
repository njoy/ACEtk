void verifyIndex( const std::size_t index ) const {

  if ( ( index < 1 ) || ( index > this->M() ) ) {

    Log::error( "Illegal index argument into the {} block", this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts an index between {} and {} inclusively",
               this->name(), 1, this->M() );
    throw std::out_of_range( this->name() );
  }
}

void verifyIndex( const std::size_t array, const std::size_t index ) const {

  verifyIndex( array );
  if ( ( index < 1 ) || ( index > this->N() ) ) {

    Log::error( "Illegal index argument into the {} block", this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts an index between {} and {} inclusively",
               this->name(), 1, this->N() );
    throw std::out_of_range( this->name() );
  }
}
