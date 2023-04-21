#ifndef NJOY_ACETK_BLOCK_SECONDARYPARTICLEINFORMATIONBLOCK
#define NJOY_ACETK_BLOCK_SECONDARYPARTICLEINFORMATIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy NTRO block with the number of reactions for
 *         each secondary particle type
 *
 *  The SecondaryParticleInformationBlock class contains the number of reactions
 *  that produce each secondary particle type as given on the PTYPE block.
 *
 *  The number of available particle types is stored in NXS(7).
 */
class SecondaryParticleInformationBlock : protected details::Base {

  /* fields */
  unsigned int ntype_;

  /* auxiliary functions */
  #include "ACEtk/block/SecondaryParticleInformationBlock/src/generateXSS.hpp"
  #include "ACEtk/block/SecondaryParticleInformationBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/SecondaryParticleInformationBlock/src/ctor.hpp"

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
   *  @brief Return the number of reactions for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto NP( std::size_t index ) const { return this->XSS( index ); }

  /**
   *  @brief Return the number of reactions for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  auto numberSecondaryParticleProductionReactions( std::size_t index ) const {

    return this->NP( index );
  }

  /**
   *  @brief Return the number of reactions for all secondary particle types
   */
  auto NPs() const { return this->XSS( 1, this->NTYPE() ); }

  /**
   *  @brief Return the number of reactions for all secondary particle types
   */
  auto numberReactions() const { return this->NPs(); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using NTRO = SecondaryParticleInformationBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
