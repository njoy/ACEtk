#ifndef NJOY_ACETK_CONTINUOUS_PROBABILITYTABLE
#define NJOY_ACETK_CONTINUOUS_PROBABILITYTABLE

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief An unresolved resonance probability table for a single incident
 *         energy value
 *
 *  The ProbabilityTable class contains the probabilities and associated
 *  values for the total, elastic, fission and capture cross sections and the
 *  heating numbers.
 */
class ProbabilityTable : protected base::ArrayData {

  /* fields */

  double incident_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */

  ProbabilityTable() = default;

  ProbabilityTable( const ProbabilityTable& ) = default;
  ProbabilityTable( ProbabilityTable&& ) = default;

  ProbabilityTable& operator=( const ProbabilityTable& ) = default;
  ProbabilityTable& operator=( ProbabilityTable&& ) = default;

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

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->incident_; }

  /**
   *  @brief Return the number of bins in the table
   */
  unsigned int numberBins() const { return this->N(); }

  /**
   *  @brief Return the cumulative probability values
   */
  auto cumulativeProbabilities() const { return this->darray( 1 ); }

  /**
   *  @brief Return the total cross section values
   */
  auto total() const { return this->darray( 2 ); }

  /**
   *  @brief Return the elastic cross section values
   */
  auto elastic() const { return this->darray( 3 ); }

  /**
   *  @brief Return the fission cross section values
   */
  auto fission() const { return this->darray( 4 ); }

  /**
   *  @brief Return the capture cross section values
   */
  auto capture() const { return this->darray( 5 ); }

  /**
   *  @brief Return the heating numbers
   */
  auto heating() const { return this->darray( 6 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
