#ifndef NJOY_ACETK_BLOCK_PROBABILITYTABLE
#define NJOY_ACETK_BLOCK_PROBABILITYTABLE

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

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
class ProbabilityTable : protected details::Base {

  /* fields */
  double incident_;
  unsigned int bins_;

  /* auxiliary functions */
  #include "ACEtk/block/ProbabilityTable/src/generateXSS.hpp"
  #include "ACEtk/block/ProbabilityTable/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/ProbabilityTable/src/ctor.hpp"

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->incident_; }

  /**
   *  @brief Return the number of bins in the table
   */
  unsigned int numberBins() const { return this->bins_; }

  /**
   *  @brief Return the cumulative probability values
   */
  auto cumulativeProbabilities() const {

    return this->XSS( 1, this->numberBins() );
  }

  /**
   *  @brief Return the total cross section values
   */
  auto total() const {

    return this->XSS( 1 + this->numberBins(), this->numberBins() );
  }

  /**
   *  @brief Return the elastic cross section values
   */
  auto elastic() const {

    return this->XSS( 1 + 2 * this->numberBins(), this->numberBins() );
  }

  /**
   *  @brief Return the fission cross section values
   */
  auto fission() const {

    return this->XSS( 1 + 3 * this->numberBins(), this->numberBins() );
  }

  /**
   *  @brief Return the capture cross section values
   */
  auto capture() const {

    return this->XSS( 1 + 4 * this->numberBins(), this->numberBins() );
  }

  /**
   *  @brief Return the heating numbers
   */
  auto heating() const {

    return this->XSS( 1 + 5 * this->numberBins(), this->numberBins() );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
