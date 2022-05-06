#ifndef NJOY_ACETK_BLOCK_DETAILS_TABULATEDPROBABILITYDISTRIBUTION
#define NJOY_ACETK_BLOCK_DETAILS_TABULATEDPROBABILITYDISTRIBUTION

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/details/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief Tabulated probability distribution data (base class)
 *
 *  The TabulatedProbabilityDistribution class contains the probability density
 *  function (PDF), the cumulative density function (CDF) and any number of
 *  additional data columns as a function of cosine for the given incident
 *  energy.
 */
class TabulatedProbabilityDistribution : protected details::Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/details/TabulatedProbabilityDistribution/src/generateXSS.hpp"
  #include "ACEtk/block/details/TabulatedProbabilityDistribution/src/verifySize.hpp"

protected:

  /* constructor */
  #include "ACEtk/block/details/TabulatedProbabilityDistribution/src/ctor.hpp"

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

} // details namespace
} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
