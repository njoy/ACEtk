PhotoatomicElectronExcitationBlock() = default;

PhotoatomicElectronExcitationBlock( const PhotoatomicElectronExcitationBlock& ) = default;
PhotoatomicElectronExcitationBlock( PhotoatomicElectronExcitationBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies    the energy values
 *  @param[in] loss        the average excitation energy loss values
 */
PhotoatomicElectronExcitationBlock(
    std::vector< double > energies,
    std::vector< double > loss ) :
  ArrayData( "EXCIT",
             std::vector< std::vector< double > > {

               std::move( energies ),
               std::move( loss )
             } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the EXCIT block in the XSS array
 *  @param[in] end     the end iterator of the EXCIT block in the XSS array
 *  @param[in] nxl     the number of energy values
 */
PhotoatomicElectronExcitationBlock( Iterator begin, Iterator end,
                                    unsigned int nxl ) :
  ArrayData( "EXCIT", begin, end, nxl, 2 ) {}

PhotoatomicElectronExcitationBlock& operator=( const PhotoatomicElectronExcitationBlock& ) = default;
PhotoatomicElectronExcitationBlock& operator=( PhotoatomicElectronExcitationBlock&& ) = default;
