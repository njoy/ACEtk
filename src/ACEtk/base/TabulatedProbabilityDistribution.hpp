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

  static std::vector< double > generateXSS(
      int interpolation,
      std::vector< double >&& values,
      std::vector< double >&& pdf,
      std::vector< double >&& cdf,
      std::vector< std::vector< double > >&& data ) {

    std::vector< double > xss = { static_cast< double >( interpolation ) };
    xss.reserve( 2 + 3 * values.size() );
    data.insert( data.begin(), std::move( cdf ) );
    data.insert( data.begin(), std::move( pdf ) );
    data.insert( data.begin(), std::move( values ) );
    ColumnData columns( "TabulatedProbabilityDistribution", std::move( data ) );
    xss.insert( xss.end(), columns.begin(), columns.end() );

    return xss;
  }

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int numberValues ) {

    auto size = std::distance( begin, end );
    if ( size < 3 * numberValues + 2 ) {

      Log::error( "The size of the XSS subrange in the tabulated "
                  "distribution data should be at least 2 + 3 * XSS(2)" );
      Log::info( "XSS(2) value: {}", numberValues );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

protected:

  /* constructor */

  TabulatedProbabilityDistribution() = default;

  TabulatedProbabilityDistribution( const TabulatedProbabilityDistribution& ) = default;
  TabulatedProbabilityDistribution( TabulatedProbabilityDistribution&& ) = default;

  TabulatedProbabilityDistribution& operator=( const TabulatedProbabilityDistribution& ) = default;
  TabulatedProbabilityDistribution& operator=( TabulatedProbabilityDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] name            the name of the block
   *  @param[in] interpolation   the interpolation type
   *  @param[in] values          the values (N values)
   *  @param[in] pdf             the pdf values (N values)
   *  @param[in] cdf             the cdf values (N values)
   *  @param[in] data            the additional data (arrays of N values)
   */
  TabulatedProbabilityDistribution( std::string name,
                                    int interpolation,
                                    std::vector< double > values,
                                    std::vector< double > pdf,
                                    std::vector< double > cdf,
                                    std::vector< std::vector< double > > data ) :
    Base( std::move( name ),
          generateXSS( interpolation,
                       std::move( values ), std::move( pdf ), std::move( cdf ),
                       std::move( data ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] name            the name of the block
   *  @param[in] interpolation   the interpolation type
   *  @param[in] values          the values (N values)
   *  @param[in] pdf             the pdf values (N values)
   *  @param[in] cdf             the cdf values (N values)
   */
  TabulatedProbabilityDistribution( std::string name,
                                    int interpolation,
                                    std::vector< double > values,
                                    std::vector< double > pdf,
                                    std::vector< double > cdf ) :
    TabulatedProbabilityDistribution(
        std::move( name ), interpolation,
        std::move( values ), std::move( pdf ), std::move( cdf ), {} ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin      the begin iterator of the tabulated distribution data
   *  @param[in] end        the end iterator of the tabulated distribution data
   */
  TabulatedProbabilityDistribution( std::string name, Iterator begin, Iterator end ) :
    Base( std::move( name ), begin, end ) {

    verifySize( this->begin(), this->end(), this->numberValues() );
  }

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
