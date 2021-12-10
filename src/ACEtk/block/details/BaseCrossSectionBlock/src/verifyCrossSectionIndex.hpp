void verifyCrossSectionIndex( const std::size_t index ) const {

  if ( ( index < 1 ) || ( index > this->NTR() ) ) {

    Log::error( "Illegal index argument into {} block", this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts an index between 1 and {} inclusively",
               this->name(), this->numberValues() );
    throw std::out_of_range( this->name() );
  }
}
