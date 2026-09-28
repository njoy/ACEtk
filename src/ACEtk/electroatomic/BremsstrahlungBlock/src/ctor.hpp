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
 *                          (or the average energy loss when NEPR = 3)
 *  @param[in] nepr         1 for remaining energy, 3 for energy loss
 */
BremsstrahlungBlock(
    std::vector< double > energies,
    std::vector< double > remaining,
    unsigned int nepr = 1 ) :
  ArrayData( "BREML",
             std::vector< std::vector< double > > {

               std::move( energies ),
               std::move( remaining )
             } ),
  nepr_( nepr ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the BREML block in the XSS array
 *  @param[in] end     the end iterator of the BREML block in the XSS array
 *  @param[in] nxl     the number of energy values
 *  @param[in] nepr    1 for remaining energy, 3 for energy loss
 */
BremsstrahlungBlock( Iterator begin, Iterator end, unsigned int nbl,
                    unsigned int nepr = 1 ) :
  ArrayData( "BREML", begin, end, nbl, 2 ),
  nepr_( nepr ) {}
