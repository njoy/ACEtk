EditCrossSectionBlock() = default;

EditCrossSectionBlock( const EditCrossSectionBlock& ) = default;
EditCrossSectionBlock( EditCrossSectionBlock&& ) = default;

EditCrossSectionBlock& operator=( const EditCrossSectionBlock& ) = default;
EditCrossSectionBlock& operator=( EditCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] reactions      the edit reaction cross section data
 */
EditCrossSectionBlock( std::vector< std::vector< double > > reactions ) :
  ColumnData( "XSED", reactions ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of XSED data
 *  @param[in] end      the end iterator of the XSED data
 *  @param[in] nedit    the number of edit reactions
 */
EditCrossSectionBlock( Iterator begin, Iterator end, unsigned int nedit ) :
  ColumnData( "XSED", begin, end, nedit ) {}
