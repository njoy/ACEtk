#ifndef NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEPRODUCTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEPRODUCTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Total production cross section and heating numbers for a secondary
 *         particle
 *
 *  The SecondaryParticleProductionBlock class contains the index of the
 *  energy point corresponding to the first cross section value, the number of
 *  cross section values and the actual production cross section values and
 *  heating numbers.
 */
class SecondaryParticleProductionBlock : protected base::Base {

  /* fields */

  /* auxiliary functions */

  static std::vector< double > generateXSS(
      std::size_t index,
      std::vector< double >&& production,
      std::vector< double >&& heating ) {

    const auto size = production.size();
    if ( heating.size() != size ) {

      Log::error( "The number of heating values is not equal to the number of "
                  "production values" );
      Log::info( "Expected size = {}", size );
      Log::info( "Found production size = {}", production.size() );
      Log::info( "Found heating size = {}", heating.size() );
      throw std::exception();
    }

    std::vector< double > xss = { static_cast< double >( index ),
                                  static_cast< double >( size ) };
    xss.reserve( 2 + 2 * size );
    xss.insert( xss.end(), production.begin(), production.end() );
    xss.insert( xss.end(), heating.begin(), heating.end() );

    return xss;
  }

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int numberValues ) {

    auto size = std::distance( begin, end );
    if ( size < 2 * numberValues + 2 ) {

      Log::error( "The size of the XSS subrange in the cross section data should "
                  "be at least 2 + 2 * XSS(2)" );
      Log::info( "XSS(2) value: {}", numberValues );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

public:

  /* constructor */

  SecondaryParticleProductionBlock() = default;

  SecondaryParticleProductionBlock( const SecondaryParticleProductionBlock& ) = default;
  SecondaryParticleProductionBlock( SecondaryParticleProductionBlock&& ) = default;

  SecondaryParticleProductionBlock& operator=( const SecondaryParticleProductionBlock& ) = default;
  SecondaryParticleProductionBlock& operator=( SecondaryParticleProductionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] index         the energy index
   *  @param[in] production    the total production cross section values
   *  @param[in] heating       the heating values
   */
  SecondaryParticleProductionBlock( std::size_t index,
                                    std::vector< double > production,
                                    std::vector< double > heating ) :
    Base( "HPD", generateXSS( index, std::move( production ),
                              std::move( heating ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the cross section data
   *  @param[in] end      the end iterator of the cross section data
   */
  SecondaryParticleProductionBlock( Iterator begin, Iterator end ) :
    Base( "HPD", begin, end ) {

    verifySize( this->begin(), this->end(), this->numberValues() );
  }

  /**
   *  @brief Return the energy index
   */
  std::size_t energyIndex() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of cross section values
   */
  std::size_t numberValues() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the total production cross section values
   */
  auto totalProduction() const {

    return this->XSS( 3, this->numberValues() );
  }

  /**
   *  @brief Return the heating numbers
   */
  auto heating() const {

    return this->XSS( 3 + this->numberValues(), this->numberValues() );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using HPD = SecondaryParticleProductionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
