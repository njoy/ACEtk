  /**
   *  @brief Return the starting index (one-based) of a row
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowStart( unsigned int row ) const {

    return std::max( row - this->NSUB(), static_cast< unsigned int >( 1 ) );   
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