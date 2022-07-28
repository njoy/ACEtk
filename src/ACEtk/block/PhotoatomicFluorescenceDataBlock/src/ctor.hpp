PhotoatomicFluorescenceDataBlock() = default;

PhotoatomicFluorescenceDataBlock( const PhotoatomicFluorescenceDataBlock& ) = default;
PhotoatomicFluorescenceDataBlock( PhotoatomicFluorescenceDataBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] edges            the edge energies
 *  @param[in] probabilities    the ejection probabilities
 *  @param[in] yields           the yields
 *  @param[in] energies         the fluorescent energies
 */
PhotoatomicFluorescenceDataBlock( std::vector< double > edges,
                                  std::vector< double > probabilities,
                                  std::vector< double > yields,
                                  std::vector< double > energies ) :
  ArrayData( "JFLO",
             std::vector< std::vector< double > > {
               std::move( edges ), std::move( probabilities ),
               std::move( yields ), std::move( energies ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the JFLO block in the XSS array
 *  @param[in] end     the end iterator of the JFLO block in the XSS array
 *  @param[in] nflo    the number of edges
 */
PhotoatomicFluorescenceDataBlock( Iterator begin, Iterator end, unsigned int nflo ) :
  ArrayData( "JFLO", begin, end, nflo, 4 ) {}

PhotoatomicFluorescenceDataBlock& operator=( const PhotoatomicFluorescenceDataBlock& ) = default;
PhotoatomicFluorescenceDataBlock& operator=( PhotoatomicFluorescenceDataBlock&& ) = default;