void verifyReactionIndex( const std::size_t index,
                          const std::size_t min,
                          const std::size_t max ) const {

  if ( ( index < min ) || ( index > max ) ) {

    Log::error( "Illegal reaction index argument into {} block", this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts a reaction index between {} and {} inclusively",
               this->name(), min, max );
    throw std::out_of_range( this->name() );
  }
}