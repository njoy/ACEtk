#ifndef NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEINFORMATIONBLOCK
#define NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEINFORMATIONBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

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
class SecondaryParticleInformationBlock : protected base::Base {

  /* fields */
  unsigned int ntype_ = 0;

  /* auxiliary functions */
  #include "ACEtk/continuous/SecondaryParticleInformationBlock/src/generateXSS.hpp"
  #include "ACEtk/continuous/SecondaryParticleInformationBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/SecondaryParticleInformationBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile and photons)
   */
  unsigned int NTYPE() const { return this->ntype_; }

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile and photons)
   */
  unsigned int numberAdditionalSecondaryParticleTypes() const {

    return this->NTYPE();
  }

  /**
   *  @brief Return the number of reactions for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int NP( std::size_t index ) const { return this->IXSS( index ); }

  /**
   *  @brief Return the number of reactions for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int numberSecondaryParticleProductionReactions( std::size_t index ) const {

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

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
