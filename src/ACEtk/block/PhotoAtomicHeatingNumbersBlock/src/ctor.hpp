PhotoAtomicHeatingNumbersBlock() = default;

PhotoAtomicHeatingNumbersBlock( const PhotoAtomicHeatingNumbersBlock& ) = default;
PhotoAtomicHeatingNumbersBlock( PhotoAtomicHeatingNumbersBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] heating    the heating numbers
 */
PhotoAtomicHeatingNumbersBlock( std::vector< double > heating ) :
  ArrayData( "LHNM",
             std::vector< std::vector< double > >{ std::move( heating ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
 *  @param[in] end     the end iterator of the ESZG block in the XSS array
 *  @param[in] nes     the number of energy points
 */
PhotoAtomicHeatingNumbersBlock( Iterator begin, Iterator end, unsigned int nes ) :
  ArrayData( "LHNM", begin, end, nes, 1 ) {}

PhotoAtomicHeatingNumbersBlock& operator=( const PhotoAtomicHeatingNumbersBlock& ) = default;
PhotoAtomicHeatingNumbersBlock& operator=( PhotoAtomicHeatingNumbersBlock&& ) = default;
