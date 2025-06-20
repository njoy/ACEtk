ElectronSubshellBlock() = default;

ElectronSubshellBlock( const ElectronSubshellBlock& ) = default;
ElectronSubshellBlock( ElectronSubshellBlock&& ) = default;

ElectronSubshellBlock& operator=( const ElectronSubshellBlock& ) = default;
ElectronSubshellBlock& operator=( ElectronSubshellBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] designators      the ENDF designator of each subshell
 *  @param[in] electrons        the electron population for each subshell
 *  @param[in] energies         the vacancy cumulative probability for each subshell
 *  @param[in] probabilities    the number of possible transitions to fill a vacancy
 *                              for each subshell
 */
ElectronSubshellBlock( std::vector< unsigned int > designators,
                       std::vector< double > electrons,
                       std::vector< double > energies,
                       std::vector< double > probabilities,
                       std::vector< unsigned int > transitions ) :
  ArrayData( "SUBSH",
             std::vector< std::vector< double > > {

               [] ( auto&& vector ) -> std::vector< double >
                  { return { vector.begin(), vector.end() }; }( designators ),
               std::move( electrons ),
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
ElectronSubshellBlock( Iterator begin, Iterator end, unsigned int nssh ) :
  ArrayData( "SUBSH", begin, end, nssh, 5 ) {}
