PhotoatomicElectronShellBlock() = default;

PhotoatomicElectronShellBlock( const PhotoatomicElectronShellBlock& ) = default;
PhotoatomicElectronShellBlock( PhotoatomicElectronShellBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] electrons        the number of electrons for each shell
 *  @param[in] energies         the binding energy for each shell
 *  @param[in] probabilities    the interaction probability for each shell
 */
PhotoatomicElectronShellBlock( std::vector< unsigned int > electrons,
                               std::vector< double > energies,
                               std::vector< double > probabilities ) :
  ArrayData( "EPS",
             std::vector< std::vector< double > > {

               [] ( auto&& vector ) -> std::vector< double >
                  { return { vector.begin(), vector.end() }; }( electrons ),
               std::move( energies ),
               std::move( probabilities )
             } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the EPS block in the XSS array
 *  @param[in] end     the end iterator of the EPS block in the XSS array
 *  @param[in] nsh     the number of electron shells
 */
PhotoatomicElectronShellBlock( Iterator begin, Iterator end, unsigned int nsh ) :
  ArrayData( "EPS", begin, end, nsh, 3 ) {}

PhotoatomicElectronShellBlock& operator=( const PhotoatomicElectronShellBlock& ) = default;
PhotoatomicElectronShellBlock& operator=( PhotoatomicElectronShellBlock&& ) = default;