#ifndef NJOY_ACETK_PHOTONUCLEAR_SECONDARYPARTICLELOCATORBLOCK
#define NJOY_ACETK_PHOTONUCLEAR_SECONDARYPARTICLELOCATORBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace photonuclear {

/**
 *  @class
 *  @brief The photonuclear IXSU block with the secondary particle information
 *         and locators
 *
 *  The SecondaryParticleLocatorBlock class contains a particle type, a number
 *  of reactions and 10 locators for each secondary particle type.
 *
 *  The number of available particle types is stored in NXS(5).
 */
class SecondaryParticleLocatorBlock : protected base::Base {

  /* fields */

  unsigned int ntype_ = 0;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( std::vector< unsigned int >&& types,
               std::vector< unsigned int >&& numbers,
               std::vector< std::array< unsigned int, 10 > >&& locators ) {

    std::vector< double > xss;
    const auto ntype = locators.size();
    xss.reserve( ntype * 12 );

    if ( ( types.size() != ntype ) || ( numbers.size() != ntype ) ) {

      Log::error( "The number of particles is not consistent between the particle types, "
                  "the number of reactions and the locator sets" );
      Log::info( "Expected: {}", ntype );
      Log::info( "Found types: {}", types.size() );
      Log::info( "Found numbers: {}", numbers.size() );
      Log::info( "Found locators: {}", locators.size() );
      throw std::exception();
    }

    for ( unsigned int index = 0; index < ntype; ++index ) {

      xss.push_back( static_cast< double >( types[index] ) );
      xss.push_back( static_cast< double >( numbers[index] ) );
      xss.insert( xss.end(), locators[index].begin(), locators[index].end() );
    }
    return xss;
  }

  static void verifySize( Iterator begin, Iterator end, unsigned int ntype ) {

    auto size = std::distance( begin, end );
    if ( size < 12 * ntype ) {

      Log::error( "The size of the XSS subrange should be at least 12 * NTYPE" );
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
      std::vector< unsigned int >&& types,
      std::vector< unsigned int >&& numbers,
      std::vector< std::array< unsigned int, 10 > >&& locators,
      std::size_t ntype ) :
    Base( "IXSU", generateXSS( std::move( types ), std::move( numbers ),
                               std::move( locators ) ) ),
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
   *  @param[in] types       the particle types
   *  @param[in] numbers     the number of reactions for each particle type
   *  @param[in] locators    the locators for each secondary particle type
   */
  SecondaryParticleLocatorBlock(
      std::vector< unsigned int > types,
      std::vector< unsigned int > numbers,
      std::vector< std::array< unsigned int, 10 > > locators ) :
    SecondaryParticleLocatorBlock(
      std::move( types ), std::move( numbers ),
      std::move( locators ), locators.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] ixs     the begin iterator of the IXS block in the XSS array
   *  @param[in] end     the end iterator of the IXS block in the XSS array
   *  @param[in] ntype   the number of secondary particle types
   */
  SecondaryParticleLocatorBlock( Iterator ixs, Iterator end, unsigned int ntype ) :
    Base( "IXSU", ixs, end ), ntype_( ntype ) {

    verifySize( this->begin(), this->end(), this->NTYPE() );
  }

  /* methods */

  /**
   *  @brief Return the number of secondary particle types
   */
  unsigned int NTYPE() const { return this->ntype_; }

  /**
   *  @brief Return the number of secondary particle types
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

    return this->IXSS( ( particle - 1 ) * 12 + index );
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
   *  @brief Return the particle type for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int IP( std::size_t index ) const {

    return this->LLOC( index, 1 );
  }

  /**
   *  @brief Return the particle type for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int particleType( std::size_t index ) const {

    return this->IP( index );
  }

  /**
   *  @brief Return the number of reactions for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int NP( std::size_t index ) const {

    return this->LLOC( index, 2 );
  }

  /**
   *  @brief Return the number of reactions for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int numberSecondaryParticleProductionReactions( std::size_t index ) const {

    return this->NP( index );
  }

  /**
   *  @brief Return the locator to the PXS block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t PXS( std::size_t index ) const {

    return this->LLOC( index, 3 );
  }

  /**
   *  @brief Return the locator to the PHN block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t PHN( std::size_t index ) const {

    return this->LLOC( index, 4 );
  }

  /**
   *  @brief Return the locator to the MTRH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t MTRH( std::size_t index ) const {

    return this->LLOC( index, 5 );
  }

  /**
   *  @brief Return the locator to the TYRH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t TYRH( std::size_t index ) const {

    return this->LLOC( index, 6 );
  }

  /**
   *  @brief Return the locator to the LSIGH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LSIGH( std::size_t index ) const {

    return this->LLOC( index, 7 );
  }

  /**
   *  @brief Return the locator to the SIGH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t SIGH( std::size_t index ) const {

    return this->LLOC( index, 8 );
  }

  /**
   *  @brief Return the locator to the LANDH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LANDH( std::size_t index ) const {

    return this->LLOC( index, 9 );
  }

  /**
   *  @brief Return the locator to the ANDH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t ANDH( std::size_t index ) const {

    return this->LLOC( index, 10 );
  }

  /**
   *  @brief Return the locator to the LDLWH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LDLWH( std::size_t index ) const {

    return this->LLOC( index, 11 );
  }

  /**
   *  @brief Return the locator to the DLWH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t DLWH( std::size_t index ) const {

    return this->LLOC( index, 12 );
  }

  /**
   *  @brief Return whether or not the particle type is present
   *
   *  @param[in] type    the particle type
   */
  bool hasIP( unsigned int type ) const {

    //! @todo use a stride view to use std::find_if instead of a handwritten loop
    for ( std::size_t index = 1; index <= this->NTYPE(); ++index ) {

        if ( this->IP( index ) == type ) {

          return true;
        }
    }
    return false;
  }

  /**
   *  @brief Return whether or not the particle type is present
   *
   *  @param[in] type    the particle type
   */
  bool hasParticleType( unsigned int reaction ) const {

    return this->hasIP( reaction );
  }

  /**
   *  @brief Return the index (one-based) of the particle type
   *
   *  @param[in] type    the particle type
   */
  std::size_t index( unsigned int type ) const {

    //! @todo use a stride view to use std::find_if instead of a handwritten loop
    for ( std::size_t index = 1; index <= this->NTYPE(); ++index ) {

        if ( this->IP( index ) == type ) {

          return index;
        }
    }

    Log::error( "The requested particle type IP{} is not present", type );
    throw std::exception();
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using IXSU = SecondaryParticleLocatorBlock;

} // photonuclear namespace
} // ACEtk namespace
} // njoy namespace

#endif
