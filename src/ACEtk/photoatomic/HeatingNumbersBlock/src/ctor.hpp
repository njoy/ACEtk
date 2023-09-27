PhotoatomicHeatingNumbersBlock() = default;

PhotoatomicHeatingNumbersBlock( const PhotoatomicHeatingNumbersBlock& ) = default;
PhotoatomicHeatingNumbersBlock( PhotoatomicHeatingNumbersBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] heating    the heating numbers
 */
PhotoatomicHeatingNumbersBlock( std::vector< double > heating ) :
  ArrayData( "LHNM",
             std::vector< std::vector< double > >{ std::move( heating ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
 *  @param[in] end     the end iterator of the ESZG block in the XSS array
 *  @param[in] nes     the number of energy points
 */
PhotoatomicHeatingNumbersBlock( Iterator begin, Iterator end, unsigned int nes ) :
  ArrayData( "LHNM", begin, end, nes, 1 ) {}

PhotoatomicHeatingNumbersBlock& operator=( const PhotoatomicHeatingNumbersBlock& ) = default;
PhotoatomicHeatingNumbersBlock& operator=( PhotoatomicHeatingNumbersBlock&& ) = default;
