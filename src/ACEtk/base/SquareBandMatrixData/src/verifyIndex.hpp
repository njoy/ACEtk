  /**
   *  @brief Verify that the row exists in the matrix
   *
   *  @param[in] row    the row index (one-based)
   */
bool verifyRow( unsigned int row ) const {
  
  // Verify row index
  if ( ( row < 1 ) || (row > this->M() ) ) {
    
    return false;
  }

  return true;
}

  /**
   *  @brief Verify that the col exists in the matrix
   *
   *  @param[in] col    the column index (one-based)
   */
bool verifyCol( unsigned int col ) const {
  
  // Verify column index
  if ( ( col < 1 ) || ( col > this->N() ) ) {
    
    return false;
  }

  return true;
}

  /**
   *  @brief Verify that the element is within the bounds of 
   *         the matrix, and exists within the diagonal bands
   *
   *  @param[in] row    the row index (one-based)
   *  @param[in] col    the column index (one-based)
   */
bool verifyIndex( std::size_t row, std::size_t col ) const {

  if ( !verifyRow( row ) || !verifyCol( col ) ) {
    
    return false;
  }
  
  // Verify that the (row,col) pair exists in the list
  if ( ( col < this->rowStart( row ) ) || ( col > this->rowEnd( row ) ) ) {
    
    return false;
  }

  return true;
}
