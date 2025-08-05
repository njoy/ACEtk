OscillatorBlock() = default;

OscillatorBlock( const OscillatorBlock& ) = default;
OscillatorBlock( OscillatorBlock&& ) = default;

OscillatorBlock& operator=( const OscillatorBlock& ) = default;
OscillatorBlock& operator=( OscillatorBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] occupationnumbers    The occupation numbers of each subshell
 *  @param[in] bindingenergies      The binding energies of each subshell
 */
OscillatorBlock( std::vector< double > occupationnumbers,
                 std::vector< double > bindingenergies ) :
  ArrayData( "OSC",
             std::move( occupationnumbers ), std::move( bindingenergies ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the OSC block in the XSS array
 *  @param[in] end     the end iterator of the OSC block in the XSS array
 *  @param[in] nosc    the number of oscillators
 */
PrincipalCrossSectionBlock( Iterator begin, Iterator end, unsigned int nosc ) :
  ArrayData( "OSC", begin, end, nosc, 2 ) {}
