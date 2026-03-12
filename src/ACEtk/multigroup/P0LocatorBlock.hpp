#ifndef NJOY_ACETK_MULTIGROUP_P0LOCATORBLOCK
#define NJOY_ACETK_MULTIGROUP_P0LOCATORBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup P0L block with locators for the P0 blocks for the
 *         incident and secondary particles
 *
 *  The P0LocatorBlock class contains NSEC+1 locators, one for the incident particle 
 *  and one for each secondary particle type given in the IPT block. The first locator
 *  is for the incident particle and the remaining are for the secondary particles, in 
 *  the same order as they are in the IPT block.
 *
 *  The number of secondary particles, NSEC, is stored in NXS(8).
 */
class P0LocatorBlock : protected base::Base {

  /* fields */
  unsigned int nsec_ = 0;

  /* auxiliary functions */
  #include "ACEtk/multigroup/P0LocatorBlock/src/generateXSS.hpp"
  #include "ACEtk/multigroup/P0LocatorBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/multigroup/P0LocatorBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of secondary particle types 
   */
  unsigned int NSEC() const { return this->nsec_; }

  /**
   *  @brief Return the number of secondary particle types 
   */
  unsigned int numberSecondaryParticleTypes() const {

    return this->NSEC();
  }

  /**
   *  @brief Return the locator for the P0 block for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based) in the IPT block
   */
  std::size_t P02( std::size_t particle ) const {

    return this->IXSS( particle + 1 );
  }

  /**
   *  @brief Return the locator for the P0 block for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based) in the IPT block
   */
  std::size_t secondaryLocator( std::size_t particle ) const {

    return this->P02( particle );
  }

  /**
   *  @brief Return the locator for the P0 block for the incident particle 
   *
   */
  std::size_t P01( ) const {

    return this->IXSS( 1 );
  }

  /**
   *  @brief Return the locator for the P0 block for the incident particle 
   *
   */
  std::size_t incidentLocator( ) const {

    return this->P01( );
  }




  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using P0L = P0LocatorBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
