#ifndef NJOY_ACETK_BASE_TABULATEDPROBABILITYDISTRIBUTION
#define NJOY_ACETK_BASE_TABULATEDPROBABILITYDISTRIBUTION

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief Tabulated probability distribution data (base class)
 *
 *  The TabulatedProbabilityDistribution class contains the probability density
 *  function (PDF), the cumulative density function (CDF) and any number of
 *  additional data columns as a function of cosine for the given incident
 *  energy.
 */
class TabulatedProbabilityDistribution : protected Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/base/TabulatedProbabilityDistribution/src/generateXSS.hpp"
  #include "ACEtk/base/TabulatedProbabilityDistribution/src/verifySize.hpp"

protected:

  /* constructor */
  #include "ACEtk/base/TabulatedProbabilityDistribution/src/ctor.hpp"

public:

  /**
   *  @brief Return the interpolation flag
   */
  int interpolation() const { return this->IXSS( 1 ); }

  /**
   *  @brief Return the number of values
   */
  std::size_t numberValues() const { return this->IXSS( 2 ); }

  /**
   *  @brief Return the values
   */
  auto values() const {

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

  /**
   *  @brief Return a column of the additional data
   */
  auto column( std::size_t index ) const {

    return this->XSS( 3 + ( 3 + index ) * this->numberValues(),
                      this->numberValues() );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
