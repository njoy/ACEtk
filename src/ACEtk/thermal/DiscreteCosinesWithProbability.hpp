#ifndef NJOY_ACETK_THERMAL_DISCRETECOSINESWITHPROBABILITY
#define NJOY_ACETK_THERMAL_DISCRETECOSINESWITHPROBABILITY

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace thermal {

/**
 *  @class
 *  @brief Discrete cosines for a single outgoing energy value used
 *         in thermal scattering secondary particle distributions
 *
 *  The DiscreteCosinesWithProbability class contains an outgoing energy value,
 *  the corresponding pdf and cdf value and the associated discrete cosine
 *  values. It is used in the ITXE block (for inelastic thermal scattering data)
 *  when IFENG = 2. This is the current standard ACE format used in inelastic
 *  thermal scattering.
 */
class DiscreteCosinesWithProbability : protected base::Base {

  /* fields */

  std::size_t ncosines_ = 0;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( double energy, double pdf, double cdf,
               std::vector< double >&& cosines ) {

    std::vector< double > xss = { energy, pdf, cdf };
    xss.insert( xss.end(), cosines.begin(), cosines.end() );
    return xss;
  }

  static void verifySize( std::size_t size, std::size_t ncosines ) {

    if ( size < 3 + ncosines ) {

      Log::error( "The size of the XSS subrange in the discrete cosine data "
                  "with probability should be at least 3 + the number of discrete "
                  "cosines" );
      Log::info( "Number discrete cosines: {}", ncosines );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  static void verifySize( Iterator begin, Iterator end, std::size_t ncosines ) {

    auto size = std::distance( begin, end );
    verifySize( size, ncosines );
  }

public:

  /* constructor */

  DiscreteCosinesWithProbability() = default;

  DiscreteCosinesWithProbability( const DiscreteCosinesWithProbability& ) = default;
  DiscreteCosinesWithProbability( DiscreteCosinesWithProbability&& ) = default;

  DiscreteCosinesWithProbability& operator=( const DiscreteCosinesWithProbability& ) = default;
  DiscreteCosinesWithProbability& operator=( DiscreteCosinesWithProbability&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energy     the outgoing energy value
   *  @param[in] pdf        the pdf value
   *  @param[in] cdf        the cdf value
   *  @param[in] cosines    the cosine values
   */
  DiscreteCosinesWithProbability(
      double energy, double pdf, double cdf,
      std::vector< double > cosines ) :
    Base( "DiscreteCosinesWithProbability",
          generateXSS( energy, pdf, cdf, std::move( cosines ) ) ),
    ncosines_( cosines.size() ) {

    verifySize( this->XSS().size(), this->numberDiscreteCosines() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] ncosines    the number of discrete cosines
   *  @param[in] begin       the begin iterator of the equiprobable bin data
   *  @param[in] end         the end iterator of the equiprobable bin data
   */
  DiscreteCosinesWithProbability(
      std::size_t ncosines,
      Iterator begin, Iterator end ) :
    Base( "DiscreteCosinesWithProbability", begin, end ),
    ncosines_( ncosines ) {

    verifySize( this->begin(), this->end(), this->numberDiscreteCosines() );
  }

  /**
   *  @brief Return the outgoing energy value
   */
  double energy() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the pdf value
   */
  double pdf() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the cdf value
   */
  double cdf() const { return this->XSS( 3 ); }

  /**
   *  @brief Return the number of discrete cosines
   */
  std::size_t NC() const { return this->ncosines_; }

  /**
   *  @brief Return the number of discrete cosines
   */
  std::size_t numberDiscreteCosines() const { return this->NC(); }

  /**
   *  @brief Return the discrete cosine values
   */
  auto cosines() const {

    return this->XSS( 4, this->numberDiscreteCosines() );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // thermal namespace
} // ACEtk namespace
} // njoy namespace

#endif
