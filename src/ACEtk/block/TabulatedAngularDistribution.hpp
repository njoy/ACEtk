#ifndef NJOY_ACETK_BLOCK_TABULATEDANGULARDISTRIBUTION
#define NJOY_ACETK_BLOCK_TABULATEDANGULARDISTRIBUTION

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/details/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated angular distirbution data from the AND block for a single
 *         reaction and incident energy
 *
 *  The TabulatedAngularDistribution class contains the probability density
 *  function (PDF) and cumulative density function (CDF) as a function of
 *  cosine for the given incident energy.
 */
class TabulatedAngularDistribution : protected details::Base {

  /* fields */
  double incident_;

  /* auxiliary functions */
  #include "ACEtk/block/TabulatedAngularDistribution/src/generateXSS.hpp"
  #include "ACEtk/block/TabulatedAngularDistribution/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/TabulatedAngularDistribution/src/ctor.hpp"

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->incident_; }

  /**
   *  @brief Return the interpolation flag
   */
  int interpolation() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t numberValues() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const {

    return this->XSS( 3, this->numberValues() );
  }

  /**
   *  @brief Return the pdf values
   */
  auto pdf() const {

    return this->XSS( 3 + this->numberValues(), this->numberValues() );
  }

  /**
   *  @brief Return the cdf values
   */
  auto cdf() const {

    return this->XSS( 3 + 2 * this->numberValues(), this->numberValues() );
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
