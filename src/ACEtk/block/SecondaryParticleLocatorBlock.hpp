#ifndef NJOY_ACETK_BLOCK_SECONDARYPARTICLELOCATORBLOCK
#define NJOY_ACETK_BLOCK_SECONDARYPARTICLELOCATORBLOCK

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy IXS block with the secondary particle locators
 *
 *  The SecondaryParticleLocatorBlock class contains 10 locators for each
 *  secondary particle type as given on the PTYPE block.
 *
 *  The number of available particle types is stored in NXS(7).
 */
class SecondaryParticleLocatorBlock : protected details::Base {

  /* fields */
  unsigned int ntype_;

  /* auxiliary functions */
  #include "ACEtk/block/SecondaryParticleLocatorBlock/src/generateXSS.hpp"
  #include "ACEtk/block/SecondaryParticleLocatorBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/SecondaryParticleLocatorBlock/src/ctor.hpp"

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
  auto LLOC( std::size_t particle, std::size_t index ) const {

    return this->XSS( ( particle - 1 ) * 10 + index );
  }

  /**
   *  @brief Return the locator for a secondary particle index and block index
   *
   *  @param[in] particle    the secondary particle index (one-based)
   *  @param[in] index       the block index (one-based)
   */
  auto locator( std::size_t particle, std::size_t index ) const {

    return this->XSS( ( particle - 1 ) * 10 + index );
  }

  /**
   *  @brief Return the locator to the HPD block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto HPD( std::size_t index ) const {

    return this->LLOC( index, 1 );
  }

  /**
   *  @brief Return the locator to the MTRH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto MTRH( std::size_t index ) const {

    return this->LLOC( index, 2 );
  }

  /**
   *  @brief Return the locator to the TYRH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto TYRH( std::size_t index ) const {

    return this->LLOC( index, 3 );
  }

  /**
   *  @brief Return the locator to the LSIGH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto LSIGH( std::size_t index ) const {

    return this->LLOC( index, 4 );
  }

  /**
   *  @brief Return the locator to the SIGH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto SIGH( std::size_t index ) const {

    return this->LLOC( index, 5 );
  }

  /**
   *  @brief Return the locator to the LANDH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto LANDH( std::size_t index ) const {

    return this->LLOC( index, 6 );
  }

  /**
   *  @brief Return the locator to the ANDH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto ANDH( std::size_t index ) const {

    return this->LLOC( index, 7 );
  }

  /**
   *  @brief Return the locator to the LDLWH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto LDLWH( std::size_t index ) const {

    return this->LLOC( index, 8 );
  }

  /**
   *  @brief Return the locator to the DLWH block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto DLWH( std::size_t index ) const {

    return this->LLOC( index, 9 );
  }

  /**
   *  @brief Return the locator to the YP block for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto YP( std::size_t index ) const {

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

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
