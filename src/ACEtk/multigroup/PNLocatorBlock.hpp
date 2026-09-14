#ifndef NJOY_ACETK_MULTIGROUP_PNLOCATORBLOCK
#define NJOY_ACETK_MULTIGROUP_PNLOCATORBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup PNL block with locators for the PN blocks for the
 *         incident and secondary particles
 *
 *  The PNLocatorBlock class contains NSEC+1 locators, one for the incident particle 
 *  and one for each secondary particle type given in the IPT block. The first locator
 *  is for the incident particle and the remaining are for the secondary particles, in 
 *  the same order as they are in the IPT block. The locators point to the PN blocks, 
 *  which contain relative locators within the PN blocks.
 *
 *  The number of secondary particles, NSEC, is stored in NXS(8).
 */
class PNLocatorBlock : protected base::Base {

  /* fields */
  unsigned int nsec_ = 0;

  /* auxiliary functions */
  #include "ACEtk/multigroup/PNLocatorBlock/src/generateXSS.hpp"
  #include "ACEtk/multigroup/PNLocatorBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/multigroup/PNLocatorBlock/src/ctor.hpp"

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
   *  @brief Return the locator for the PN block for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based) in the IPT block
   */
  std::size_t LPN( std::size_t particle ) const {

    return this->IXSS( particle + 1 );
  }

  /**
   *  @brief Return the locator for the PN block for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based) in the IPT block
   */
  std::size_t secondaryLocator( std::size_t particle ) const {

    return this->LPN( particle );
  }

  /**
   *  @brief Return the locator for the PN block for the incident particle 
   *
   */
  std::size_t LPN1( ) const {

    return this->IXSS( 1 );
  }

  /**
   *  @brief Return the locator for the PN block for the incident particle 
   *
   */
  std::size_t incidentLocator( ) const {

    return this->LPN1( );
  }

  /**
   *  @brief Return whether or not the secondary particle angular distribution is isotropic 
   *
   *  @param[in] particle    the secondary particle index (one-based) in the IPT block
   */
  bool isIsotropic( unsigned int particle ) const {

    return this->LPN( particle ) == 0;
  }

  /**
   *  @brief Return whether or not the incident particle outgoing angular distribution is isotropic 
   *
   */
  bool incidentIsotropic( ) const {

    return this->LPN1() == 0;
  }





  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using PNL = PNLocatorBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
