BremsstrahlungBlock() = default;

BremsstrahlungBlock( const BremsstrahlungBlock& ) = default;
BremsstrahlungBlock( BremsstrahlungBlock&& ) = default;

BremsstrahlungBlock& operator=( const BremsstrahlungBlock& ) = default;
BremsstrahlungBlock& operator=( BremsstrahlungBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies     the energy values
 *  @param[in] remaining    the average energy remaining after Bremsstrahlung
 */
BremsstrahlungBlock(
    std::vector< double > energies,
    std::vector< double > remaining ) :
  ArrayData( "BREML",
             std::vector< std::vector< double > > {

               std::move( energies ),
               std::move( remaining )
             } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the BREML block in the XSS array
 *  @param[in] end     the end iterator of the BREML block in the XSS array
 *  @param[in] nxl     the number of energy values
 */
BremsstrahlungBlock( Iterator begin, Iterator end, unsigned int nbl ) :
  ArrayData( "BREML", begin, end, nbl, 2 ) {}
