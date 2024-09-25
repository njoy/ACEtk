HeatingNumbersBlock() = default;

HeatingNumbersBlock( const HeatingNumbersBlock& ) = default;
HeatingNumbersBlock( HeatingNumbersBlock&& ) = default;

HeatingNumbersBlock& operator=( const HeatingNumbersBlock& ) = default;
HeatingNumbersBlock& operator=( HeatingNumbersBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] heating    the heating numbers
 */
HeatingNumbersBlock( std::vector< double > heating ) :
  ArrayData( "LHNM",
             std::vector< std::vector< double > >{ std::move( heating ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
 *  @param[in] end     the end iterator of the ESZG block in the XSS array
 *  @param[in] nes     the number of energy points
 */
HeatingNumbersBlock( Iterator begin, Iterator end, unsigned int nes ) :
  ArrayData( "LHNM", begin, end, nes, 1 ) {}
