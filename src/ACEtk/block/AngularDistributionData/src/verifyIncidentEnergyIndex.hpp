void verifyReactionIndex( const std::size_t index ) const {

  if ( ( index < 1 ) || ( index > this->numberIncidentEnergies() ) ) {

    Log::error( "Illegal incident energy index argument into {} block",
                this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts a reaction index between 1 and {} inclusively",
               this->name(), this->this->numberIncidentEnergies() );
    throw std::out_of_range( this->name() );
  }
}
