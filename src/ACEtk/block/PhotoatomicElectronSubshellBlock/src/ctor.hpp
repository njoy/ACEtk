PhotoatomicElectronSubshellBlock() = default;

PhotoatomicElectronSubshellBlock( const PhotoatomicElectronSubshellBlock& ) = default;
PhotoatomicElectronSubshellBlock( PhotoatomicElectronSubshellBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] electrons        the number of electrons for each shell
 *  @param[in] energies         the binding energy for each shell
 *  @param[in] probabilities    the interaction probability for each shell
 */
PhotoatomicElectronSubshellBlock( std::vector< unsigned int > designators,
                                  std::vector< unsigned int > electrons,
                                  std::vector< double > energies,
                                  std::vector< double > probabilities,
                                  std::vector< unsigned int > transitions ) :
  ArrayData( "SUBSH",
             std::vector< std::vector< double > > {

               [] ( auto&& vector ) -> std::vector< double >
                  { return { vector.begin(), vector.end() }; }( designators ),
               [] ( auto&& vector ) -> std::vector< double >
                  { return { vector.begin(), vector.end() }; }( electrons ),
               std::move( energies ),
               std::move( probabilities ),
               [] ( auto&& vector ) -> std::vector< double >
                  { return { vector.begin(), vector.end() }; }( transitions )
             } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the SUBSH block in the XSS array
 *  @param[in] end     the end iterator of the SUBSH block in the XSS array
 *  @param[in] nsh     the number of electron shells
 */
PhotoatomicElectronSubshellBlock( Iterator begin, Iterator end, unsigned int nssh ) :
  ArrayData( "SUBSH", begin, end, nssh, 5 ) {}

PhotoatomicElectronSubshellBlock& operator=( const PhotoatomicElectronSubshellBlock& ) = default;
PhotoatomicElectronSubshellBlock& operator=( PhotoatomicElectronSubshellBlock&& ) = default;
