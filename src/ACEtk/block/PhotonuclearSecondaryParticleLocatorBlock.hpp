#ifndef NJOY_ACETK_BLOCK_PHOTONUCLEARSECONDARYPARTICLELOCATORBLOCK
#define NJOY_ACETK_BLOCK_PHOTONUCLEARSECONDARYPARTICLELOCATORBLOCK

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photonuclear IXSU block with the secondary particle information
 *         and locators
 *
 *  The PhotonuclearSecondaryParticleLocatorBlock class contains a particle type,
 *  a number of reactions and 10 locators for each secondary particle type.
 *
 *  The number of available particle types is stored in NXS(5).
 */
class PhotonuclearSecondaryParticleLocatorBlock : protected details::Base {

  /* fields */
  unsigned int ntype_ = 0;

  /* auxiliary functions */
  #include "ACEtk/block/PhotonuclearSecondaryParticleLocatorBlock/src/generateXSS.hpp"
  #include "ACEtk/block/PhotonuclearSecondaryParticleLocatorBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/PhotonuclearSecondaryParticleLocatorBlock/src/ctor.hpp"

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

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using IXSU = PhotonuclearSecondaryParticleLocatorBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
