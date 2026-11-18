#ifndef NJOY_ACETK_THERMAL_DISCRETECOSINES
#define NJOY_ACETK_THERMAL_DISCRETECOSINES

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
 *  The DiscreteCosines class contains an outgoing energy value and the
 *  associated discrete cosine values. It is used in the ITXE block (for
 *  inelastic thermal scattering data) when IFENG = 0 or 1.
 */
class DiscreteCosines : protected base::Base {

  /* fields */

  std::size_t ncosines_ = 0;

  /* auxiliary functions */

  static void verifySize( std::size_t size, std::size_t ncosines ) {

    if ( size < 1 + ncosines ) {

      Log::error( "The size of the XSS subrange in the discrete cosine data "
                  "should be at least 1 + the number of discrete cosines" );
      Log::info( "Number discrete cosines: {}", ncosines );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  static void verifySize( Iterator begin, Iterator end, std::size_t ncosines ) {

    auto size = std::distance( begin, end );
    verifySize( size, ncosines );
  }

  static std::vector< double >
  generateXSS( double energy, std::vector< double >&& cosines ) {

    std::vector< double > xss = { energy };
    xss.insert( xss.end(), cosines.begin(), cosines.end() );
    return xss;
  }

public:

  /* constructor */

  DiscreteCosines() = default;

  DiscreteCosines( const DiscreteCosines& ) = default;
  DiscreteCosines( DiscreteCosines&& ) = default;

  DiscreteCosines& operator=( const DiscreteCosines& ) = default;
  DiscreteCosines& operator=( DiscreteCosines&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energy     the outgoing energy value
   *  @param[in] cosines    the discrete cosine values
   */
  DiscreteCosines( double energy, std::vector< double > cosines ) :
    Base( "DiscreteCosines", generateXSS( energy, std::move( cosines ) ) ),
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
  DiscreteCosines( std::size_t ncosines, Iterator begin, Iterator end ) :
    Base( "DiscreteCosines", begin, end ),
    ncosines_( ncosines ) {

    verifySize( this->begin(), this->end(), this->numberDiscreteCosines() );
  }

  /**
   *  @brief Return the outgoing energy value
   */
  double energy() const { return this->XSS( 1 ); }

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

    return this->XSS( 2, this->numberDiscreteCosines() );
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
