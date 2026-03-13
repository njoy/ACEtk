
  /**
   *  @brief Return the starting index (one-based) of a row
   *         in the list of values
   *
   *  @param[in] row     the row index in the matrix (one-based)
   */
unsigned int rowListStart( unsigned int row ) const {

    unsigned int index = 0;

    // get length of rows above desired row to
    // find the start index of desired row
    for (int i = row - 1; i > 0; --i) {
        index = index + this->rowLength( i );
    }

    return index + 1;
}

  /**
   *  @brief Return the index (one-based) of an element
   *         in the list of values
   *
   *  This function assumes the element exists in the list - the
   *  behavior is undefined if the element is not. The verifyIndex
   *  method should always be called before this method.
   *
   *  @param[in] row     the row index in the matrix (one-based)
   *  @param[in] col     the col index in the matrix (one-based)
   */
unsigned int listIndex( unsigned int row, unsigned int col ) const {

    unsigned int index = rowListStart( row );
    return index + ( col - this->rowStart( row ) ) ;
}