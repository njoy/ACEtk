#ifndef NJOY_ACETK_CONTINUOUS_PROBABILITYTABLE
#define NJOY_ACETK_CONTINUOUS_PROBABILITYTABLE

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

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
  #include "ACEtk/continuous/ProbabilityTable/src/ctor.hpp"

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

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
