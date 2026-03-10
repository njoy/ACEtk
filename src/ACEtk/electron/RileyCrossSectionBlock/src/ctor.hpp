RileyCrossSectionBlock() = default;

RileyCrossSectionBlock( const RileyCrossSectionBlock& ) = default;
RileyCrossSectionBlock( RileyCrossSectionBlock&& ) = default;

RileyCrossSectionBlock& operator=( const RileyCrossSectionBlock& ) = default;
RileyCrossSectionBlock& operator=( RileyCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] rileySet256keV    the Riley cross section parameters at 256 keV
 *  @param[in] rileySet128keV    the Riley cross section parameters at 128 keV
 *  @param[in] rileySet64keV     the Riley cross section parameters at 64 keV
 *  @param[in] rileySet32keV     the Riley cross section parameters at 32 keV
 *  @param[in] rileySet16keV     the Riley cross section parameters at 16 keV
 *  @param[in] rileySet8keV      the Riley cross section parameters at 8 keV
 *  @param[in] rileySet4keV      the Riley cross section parameters at 4 keV
 *  @param[in] rileySet2keV      the Riley cross section parameters at 2 keV
 *  @param[in] rileySet1keV      the Riley cross section parameters at 1 keV
 */
RileyCrossSectionBlock( std::vector< double > rileySet256keV,
                        std::vector< double > rileySet128keV,
                        std::vector< double > rileySet64keV,
                        std::vector< double > rileySet32keV,
                        std::vector< double > rileySet16keV,
                        std::vector< double > rileySet8keV,
                        std::vector< double > rileySet4keV,
                        std::vector< double > rileySet2keV,
                        std::vector< double > rileySet1keV ) :
  ArrayData( "RLY",
             std::vector< std::vector< double > > {
                 rileySet256keV, rileySet128keV, rileySet64keV,
                 rileySet32keV, rileySet16keV, rileySet8keV,
                 rileySet4keV, rileySet2keV, rileySet1keV } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
 *  @param[in] end     the end iterator of the ESZG block in the XSS array
 */
RileyCrossSectionBlock( Iterator begin, Iterator end ) :
  ArrayData( "RLY", begin, end, 14, 9 ) {}
