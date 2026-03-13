  /**
   *  @brief Return the starting index (one-based) of a row
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowStart( int row ) const {

    // Have to have signed ints here because this equation relies on the
    // ability of the first term to go negative when the row is filled
    // in all the way to first column, so that the max function gives 1. 
    // To avoid casting to signed int, the logic would need to be changed.
    return std::max( row - static_cast< int >( this->NSUB() ),  1  );    
  }

  /**
   *  @brief Return the ending index (one-based) of a row
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowEnd( unsigned int row ) const {

    return std::min( this->size(), row + this->NSUP() );
  }


  /**
   *  @brief Return the length of a row
   *
   *  The length includes both the starting index and the ending
   *  index, so it is 1 + (end - start)
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowLength( unsigned int row ) const {

        return 1 + this->rowEnd(row) - this->rowStart(row) ;
  }