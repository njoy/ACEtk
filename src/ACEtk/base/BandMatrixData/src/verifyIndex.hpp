  /**
   *  @brief Verify that the row exists in the matrix
   *
   *  @param[in] row    the row index (one-based)
   */
void verifyRow( unsigned int row ) const {
  
  // Verify row index
  if ( ( row < 1 ) || (row > this->M() ) ) {
    
    Log::error( "Illegal row index argument into the {} block", this->name() );
    Log::info( "Row index value: {}", row );
    Log::info( "{} accepts an index between {} and {} inclusively",
               this->name(), 1, this->M() );
    throw std::out_of_range( this->name() );
  }
}

  /**
   *  @brief Verify that the col exists in the matrix
   *
   *  @param[in] col    the column index (one-based)
   */
void verifyCol( unsigned int col ) const {
  
  // Verify column index
  if ( ( col < 1 ) || (col > this->N() ) ) {
    
    Log::error( "Illegal column index argument into the {} block", this->name() );
    Log::info( "Column index value: {}", col );
    Log::info( "{} accepts an index between {} and {} inclusively",
               this->name(), 1, this->N() );
    throw std::out_of_range( this->name() );
  }
}

  /**
   *  @brief Verify that the element is within the bounds of 
   *         the matrix, and exists within the diagonal bands
   *
   *  @param[in] row    the row index (one-based)
   *  @param[in] col    the column index (one-based)
   */
void verifyIndex( std::size_t row, std::size_t col ) const {

  verifyRow( row );
  verifyCol( col );
  
  // Verify that the (row,col) pair exists in the list
  if ( ( col < this->rowStart(row) ) || (col > this->rowEnd(row) ) ) {
    
    Log::error( "Illegal index argument into the {} block", this->name() );
    Log::info( "Row index value: {}", row );
    Log::info( "Column index value: {}", col );
    Log::info( "Row {} accepts a col index between {} and {} inclusively",
               row, this->rowStart(row), this->rowEnd(row) );
    throw std::out_of_range( this->name() );
  }
}
