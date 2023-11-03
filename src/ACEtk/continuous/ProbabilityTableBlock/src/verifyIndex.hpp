void verifyIndex( const std::size_t index ) const {

  if ( ( index < 1 ) || ( index > this->N() ) ) {

    Log::error( "Illegal index argument into the {} block", this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts an index between 1 and {} inclusively",
               this->name(), this->N() );
    throw std::out_of_range( this->name() );
  }
}
