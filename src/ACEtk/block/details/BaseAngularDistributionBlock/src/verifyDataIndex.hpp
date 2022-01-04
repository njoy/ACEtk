void verifyDataIndex( const std::size_t index ) const {

  if ( ( index < this->zero_index_ ? 0 : 1 ) || ( index > this->NR() ) ) {

    Log::error( "Illegal index argument into the {} block", this->name() );
    Log::info( "Index value: {}", index );
    Log::info( "{} accepts an index between {} and {} inclusively",
               this->name(), this->zero_index_ ? 0 : 1, this->NR() );
    throw std::out_of_range( this->name() );
  }
}
