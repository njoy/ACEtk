#ifndef NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLELOCATORBLOCK
#define NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLELOCATORBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy IXS block with the secondary particle locators
 *
 *  The SecondaryParticleLocatorBlock class contains 10 locators for each
 *  secondary particle type as given on the PTYPE block.
 *
 *  The number of available particle types is stored in NXS(7).
 */
class SecondaryParticleLocatorBlock : protected base::Base {

  /* fields */

  unsigned int ntype_ = 0;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( std::vector< std::array< unsigned int, 10 > >&& locators ) {

    std::vector< double > xss;
    const auto ntype = locators.size();
    xss.reserve( ntype * 10 );
    for ( const auto& array : locators ) {

      xss.insert( xss.end(), array.begin(), array.end() );
    }
    return xss;
  }

  static void verifySize( Iterator begin, Iterator end, unsigned int ntype ) {

    auto size = std::distance( begin, end );
    if ( size < 10 * ntype ) {

      Log::error( "The size of the XSS subrange should be at least 10 * NTYPE" );
      Log::info( "NTYPE value: {}", ntype );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  SecondaryParticleLocatorBlock(
      std::vector< std::array< unsigned int, 10 > >&& locators,
      std::size_t ntype ) :
    Base( "IXS", generateXSS( std::move( locators ) ) ),
    ntype_( ntype ) {}

public:

  /* constructor */

  SecondaryParticleLocatorBlock() = default;

  SecondaryParticleLocatorBlock( const SecondaryParticleLocatorBlock& ) = default;
  SecondaryParticleLocatorBlock( SecondaryParticleLocatorBlock&& ) = default;

  SecondaryParticleLocatorBlock& operator=( const SecondaryParticleLocatorBlock& ) = default;
  SecondaryParticleLocatorBlock& operator=( SecondaryParticleLocatorBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] locators    the locators for each secondary particle type
   */
  SecondaryParticleLocatorBlock(
      std::vector< std::array< unsigned int, 10 > > locators ) :
    SecondaryParticleLocatorBlock( std::move( locators ), locators.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] ixs     the begin iterator of the IXS block in the XSS array
   *  @param[in] end     the end iterator of the IXS block in the XSS array
   *  @param[in] ntype   the number of secondary particle types
   */
  SecondaryParticleLocatorBlock( Iterator ixs, Iterator end, unsigned int ntype ) :
    Base( "IXS", ixs, end ), ntype_( ntype ) {

    verifySize( this->begin(), this->end(), this->NTYPE() );
  }

  /* methods */

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile)
   */
  unsigned int NTYPE() const { return this->ntype_; }

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile)
   */
  unsigned int numberAdditionalSecondaryParticleTypes() const {

    return this->NTYPE();
  }

  /**
   *  @brief Return the locator for a secondary particle index and block index
   *
   *  @param[in] particle    the secondary particle index (one-based)
   *  @param[in] index       the block index (one-based)
   */
  std::size_t LLOC( std::size_t particle, std::size_t index ) const {

    return this->IXSS( ( particle - 1 ) * 10 + index );
  }

  /**
   *  @brief Return the locator for a secondary particle index and block index
   *
   *  @param[in] particle    the secondary particle index (one-based)
   *  @param[in] index       the block index (one-based)
   */
  std::size_t locator( std::size_t particle, std::size_t index ) const {

    return this->LLOC( particle, index );
  }

  /**
   *  @brief Return the locator to the HPD block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t HPD( std::size_t index ) const {

    return this->LLOC( index, 1 );
  }

  /**
   *  @brief Return the locator to the MTRH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t MTRH( std::size_t index ) const {

    return this->LLOC( index, 2 );
  }

  /**
   *  @brief Return the locator to the TYRH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t TYRH( std::size_t index ) const {

    return this->LLOC( index, 3 );
  }

  /**
   *  @brief Return the locator to the LSIGH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LSIGH( std::size_t index ) const {

    return this->LLOC( index, 4 );
  }

  /**
   *  @brief Return the locator to the SIGH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t SIGH( std::size_t index ) const {

    return this->LLOC( index, 5 );
  }

  /**
   *  @brief Return the locator to the LANDH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LANDH( std::size_t index ) const {

    return this->LLOC( index, 6 );
  }

  /**
   *  @brief Return the locator to the ANDH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t ANDH( std::size_t index ) const {

    return this->LLOC( index, 7 );
  }

  /**
   *  @brief Return the locator to the LDLWH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LDLWH( std::size_t index ) const {

    return this->LLOC( index, 8 );
  }

  /**
   *  @brief Return the locator to the DLWH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t DLWH( std::size_t index ) const {

    return this->LLOC( index, 9 );
  }

  /**
   *  @brief Return the locator to the YP block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t YP( std::size_t index ) const {

    return this->LLOC( index, 10 );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using IXS = SecondaryParticleLocatorBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
