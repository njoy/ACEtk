private:

template < typename Number >
ArrayData( std::string&& name, std::vector< std::vector< Number > >&& values,
           unsigned int n, unsigned int m ) :
  Base( std::move( name ), generateXSS( std::move( values ) ) ),
  nelements_( n ), narrays_( m ) {}

protected:

ArrayData() = default;

ArrayData( const ArrayData& ) = default;
ArrayData( ArrayData&& ) = default;

/**
 *  @brief Convenience constructor
 *
 *  @param[in] name     the name of the block
 *  @param[in] values   the values
 */
template < typename Number >
ArrayData( std::string&& name, std::vector< std::vector< Number > >&& values ) :
  ArrayData( std::move( name ), std::move( values ), values.front().size(),
             values.size() ) {}

/**
 *  @brief Convenience constructor
 *
 *  @param[in] name     the name of the block
 *  @param[in] array1   the values for array 1
 *  @param[in] array2   the values for array 2
 */
template < typename Number >
ArrayData( std::string&& name,
           std::vector< Number >&& array1,
           std::vector< Number >&& array2 ) :
  ArrayData( std::move( name ),
             std::vector< std::vector< Number > >{

               std::move( array1 ), std::move( array2 ) } ) {}

/**
 *  @brief Convenience constructor
 *
 *  @param[in] name     the name of the block
 *  @param[in] array1   the values for array 1
 *  @param[in] array2   the values for array 2
 *  @param[in] array3   the values for array 3
 */
template < typename Number >
ArrayData( std::string&& name,
           std::vector< Number >&& array1,
           std::vector< Number >&& array2,
           std::vector< Number >&& array3 ) :
  ArrayData( std::move( name ),
             std::vector< std::vector< Number > >{

               std::move( array1 ), std::move( array2 ),
               std::move( array3 )
             } ) {}

/**
 *  @brief Convenience constructor
 *
 *  @param[in] name     the name of the block
 *  @param[in] array1   the values for array 1
 *  @param[in] array2   the values for array 2
 *  @param[in] array3   the values for array 3
 *  @param[in] array4   the values for array 4
 */
template < typename Number >
ArrayData( std::string&& name,
           std::vector< Number >&& array1,
           std::vector< Number >&& array2,
           std::vector< Number >&& array3,
           std::vector< Number >&& array4 ) :
  ArrayData( std::move( name ),
             std::vector< std::vector< Number > >{

               std::move( array1 ), std::move( array2 ),
               std::move( array3 ), std::move( array4 )
             } ) {}

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
template < typename Number >
ArrayData( std::string&& name,
           std::vector< Number >&& array1,
           std::vector< Number >&& array2,
           std::vector< Number >&& array3,
           std::vector< Number >&& array4,
           std::vector< Number >&& array5 ) :
  ArrayData( std::move( name ),
             std::vector< std::vector< Number > >{

               std::move( array1 ), std::move( array2 ),
               std::move( array3 ), std::move( array4 ),
               std::move( array5 )
             } ) {}

/**
 *  @brief Convenience constructor
 *
 *  @param[in] name     the name of the block
 *  @param[in] array1   the values for array 1
 *  @param[in] array2   the values for array 2
 *  @param[in] array3   the values for array 3
 *  @param[in] array4   the values for array 4
 *  @param[in] array5   the values for array 5
 *  @param[in] array6   the values for array 6
 */
template < typename Number >
ArrayData( std::string&& name,
           std::vector< Number >&& array1,
           std::vector< Number >&& array2,
           std::vector< Number >&& array3,
           std::vector< Number >&& array4,
           std::vector< Number >&& array5,
           std::vector< Number >&& array6 ) :
  ArrayData( std::move( name ),
             std::vector< std::vector< Number > >{

               std::move( array1 ), std::move( array2 ),
               std::move( array3 ), std::move( array4 ),
               std::move( array5 ), std::move( array6 )
             } ) {}

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
