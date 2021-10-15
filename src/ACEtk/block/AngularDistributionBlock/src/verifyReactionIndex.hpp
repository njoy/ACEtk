void verifyReactionIndex( const std::size_t index ) const {

  if ( ( index < 1 ) || ( index > this->ntr_ ) ) {

    Log::error( "Illegal reaction index argument into {} block", this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts a reaction index between 1 and {} inclusively",
               this->name(), this->ntr_ );
    throw std::out_of_range( this->name() );
  }
}
