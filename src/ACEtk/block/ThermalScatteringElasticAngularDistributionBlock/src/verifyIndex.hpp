void verifyIndex( const std::size_t index ) const {

  if ( ( index < 0 ) || ( index > this->NE() ) ) {

    Log::error( "Illegal index argument into the {} block", this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts an index between {} and {} inclusively",
               this->name(), 1, this->NE() );
    throw std::out_of_range( this->name() );
  }
}
