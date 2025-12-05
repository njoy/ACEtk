ElectronShellBlock() = default;

ElectronShellBlock( const ElectronShellBlock& ) = default;
ElectronShellBlock( ElectronShellBlock&& ) = default;

ElectronShellBlock& operator=( const ElectronShellBlock& ) = default;
ElectronShellBlock& operator=( ElectronShellBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] electrons        the number of electrons for each shell
 *  @param[in] energies         the binding energy for each shell
 *  @param[in] probabilities    the interaction probability for each shell
 */
ElectronShellBlock( std::vector< double > electrons,
                    std::vector< double > energies,
                    std::vector< double > probabilities ) :
  ArrayData( "EPS",
             std::vector< std::vector< double > > {

               std::move( electrons ),
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
ElectronShellBlock( Iterator begin, Iterator end, unsigned int nsh ) :
  ArrayData( "EPS", begin, end, nsh, 3 ) {}
