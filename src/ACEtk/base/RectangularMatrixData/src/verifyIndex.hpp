void verifyIndex( std::size_t row, std::size_t col ) const {
  
  // Verify row index
  if ( ( row < 1 ) || (row > this->M() ) ) {
    
    Log::error( "Illegal row index argument into the {} block", this->name() );
    Log::info( "Row index value: {}", row );
    Log::info( "{} accepts an index between {} and {} inclusively",
               this->name(), 1, this->M() );
    throw std::out_of_range( this->name() );
  }
  
  // Verify column index
  if ( ( col < 1 ) || (col > this->N() ) ) {
    
    Log::error( "Illegal column index argument into the {} block", this->name() );
    Log::info( "Column index value: {}", col );
    Log::info( "{} accepts an index between {} and {} inclusively",
               this->name(), 1, this->N() );
    throw std::out_of_range( this->name() );
  }
}
