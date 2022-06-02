private:

ArrayData( std::string&& name, std::vector< std::vector< double > >&& values,
           unsigned int n, unsigned int m ) :
  Base( std::move( name ), generateXSS( std::move( values ) ) ),
  nelements_( n ), narrays_( m ) {}

protected:

ArrayData() = default;

ArrayData( const ArrayData& ) = default;
ArrayData( ArrayData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] name     the name of the block
 *  @param[in] values   the values
 */
ArrayData( std::string&& name, std::vector< std::vector< double > >&& values ) :
  ArrayData( std::move( name ), std::move( values ), values.front().size(),
             values.size() ) {}

/**
 *  @brief Convenience constructor
 *
 *  @param[in] name     the name of the block
 *  @param[in] array1   the values for array 1
 *  @param[in] array2   the values for array 2
 *  @param[in] array3   the values for array 3
 *  @param[in] array4   the values for array 4
 *  @param[in] array5   the values for array 5
 */
ArrayData( std::string&& name,
           std::vector< double >&& array1,
           std::vector< double >&& array2,
           std::vector< double >&& array3,
           std::vector< double >&& array4,
           std::vector< double >&& array5 ) :
  ArrayData( std::move( name ),
             { std::move( array1 ), std::move( array2 ),
               std::move( array3 ), std::move( array4 ),
               std::move( array5 ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the array data in the XSS array
 *  @param[in] end     the end iterator of the array data in the XSS array
 *  @param[in] n       the number of values in each array
 *  @param[in] m       the number of arrays
 */
ArrayData( std::string&& name,
           Iterator begin, Iterator end, unsigned int n, unsigned int m ) :
  Base( std::move( name ), begin, end ), nelements_( n ), narrays_( m ) {

  verifySize( this->begin(), this->end(), this->nelements_, this->narrays_ );
}

ArrayData& operator=( const ArrayData& ) = default;
ArrayData& operator=( ArrayData&& ) = default;
