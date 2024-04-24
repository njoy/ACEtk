ProbabilityTable() = default;

ProbabilityTable( const ProbabilityTable& ) = default;
ProbabilityTable( ProbabilityTable&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident         the incident energy value
 *  @param[in] probabilities    the probability values
 *  @param[in] total            the total cross section values
 *  @param[in] elastic          the elastic cross section values
 *  @param[in] fission          the fission cross section values
 *  @param[in] capture          the capture cross section values
 *  @param[in] heating          the heating numbers
 */
ProbabilityTable( double incident,
                  std::vector< double > probabilities,
                  std::vector< double > total,
                  std::vector< double > elastic,
                  std::vector< double > fission,
                  std::vector< double > capture,
                  std::vector< double > heating ) :
  ArrayData( "ProbabilityTable",
             std::move( probabilities ), std::move( total ),
             std::move( elastic ), std::move( fission ),
             std::move( capture ), std::move( heating ) ),
  incident_( incident ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] incident         the incident energy value
 *  @param[in] probabilities    the probability values
 *  @param[in] total            the total cross section values
 *  @param[in] elastic          the elastic cross section values
 *  @param[in] capture          the capture cross section values
 *  @param[in] heating          the heating numbers
 */
ProbabilityTable( double incident,
                  std::vector< double > total,
                  std::vector< double > probabilities,
                  std::vector< double > elastic,
                  std::vector< double > capture,
                  std::vector< double > heating ) :
 ProbabilityTable(
     incident, std::move( probabilities ), std::move( total ),
     std::move( elastic ),
     std::vector< double >( static_cast< unsigned int >( total.size() ), 0. ),
     std::move( capture ), std::move( heating ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the multiplicity data in the XSS array
 *  @param[in] end      the end iterator of the multiplicity data in the XSS array
 */
ProbabilityTable( Iterator begin, Iterator end,
                  double incident, std::size_t bins ) :
  ArrayData( "ProbabilityTable", begin, end, bins, 6 ),
  incident_( incident ) {}

ProbabilityTable& operator=( const ProbabilityTable& ) = default;

ProbabilityTable& operator=( ProbabilityTable&& ) = default;
