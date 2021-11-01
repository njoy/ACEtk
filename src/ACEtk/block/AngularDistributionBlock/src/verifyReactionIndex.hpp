void verifyReactionIndex( const std::size_t index ) const {

  if ( ( index < 0 ) || ( index > this->nr_ ) ) {

    Log::error( "Illegal reaction index argument into {} block", this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts a reaction index between 0 and {} inclusively",
               this->name(), this->nr_ );
    throw std::out_of_range( this->name() );
  }
}
