AbsorptionCrossSectionBlock() = default;

AbsorptionCrossSectionBlock( const AbsorptionCrossSectionBlock& ) = default;
AbsorptionCrossSectionBlock( AbsorptionCrossSectionBlock&& ) = default;

AbsorptionCrossSectionBlock& operator=( const AbsorptionCrossSectionBlock& ) = default;
AbsorptionCrossSectionBlock& operator=( AbsorptionCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] absorptionCrossSection      the absorption cross section for each group
 */
AbsorptionCrossSectionBlock( std::vector< double > absorptionCrossSection ) :
  ArrayData( "ABS", std::vector< std::vector< double > >{ std::move( absorptionCrossSection ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the FISS block in the XSS array
 *  @param[in] end     the end iterator of the FISS block in the XSS array
 *  @param[in] ngrp     the number of energy groups
 */
AbsorptionCrossSectionBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
  ArrayData( "ABS", begin, end, ngrp, 1 ) {}
