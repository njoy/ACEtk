#ifndef NJOY_ACETK_MULTIGROUP_XPNLOCATORBLOCK
#define NJOY_ACETK_MULTIGROUP_XPNLOCATORBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup XPNL block with locators for the XPN blocks for the
 *         incident and secondary particles
 *
 *  The XPNLocatorBlock class contains NSEC+1 locators, one for the incident particle 
 *  and one for each secondary particle type given in the IPT block. The first locator
 *  is for the incident particle and the remaining are for the secondary particles, in 
 *  the same order as they are in the IPT block. The locators point to the XPN blocks, 
 *  which contain relative locators within the PN blocks.
 *
 *  The number of secondary particles, NSEC, is stored in NXS(8).
 */
class XPNLocatorBlock : protected base::Base {

  /* fields */
  unsigned int nsec_ = 0;

  /* auxiliary functions */
  #include "ACEtk/multigroup/XPNLocatorBlock/src/generateXSS.hpp"
  #include "ACEtk/multigroup/XPNLocatorBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/multigroup/XPNLocatorBlock/src/ctor.hpp"

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
   *  @brief Return the locator for the XPN block for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based) in the IPT block
   */
  std::size_t LXPN( std::size_t particle ) const {

    return this->IXSS( particle + 1 );
  }

  /**
   *  @brief Return the locator for the XPN block for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based) in the IPT block
   */
  std::size_t secondaryLocator( std::size_t particle ) const {

    return this->LXPN( particle );
  }

  /**
   *  @brief Return the locator for the XPN block for the incident particle 
   *
   */
  std::size_t LXPN1( ) const {

    return this->IXSS( 1 );
  }

  /**
   *  @brief Return the locator for the XPN block for the incident particle 
   *
   */
  std::size_t incidentLocator( ) const {

    return this->LXPN1( );
  }

  /**
   *  @brief Return whether or not the secondary particle angular distribution is isotropic 
   *
   *  @param[in] particle    the secondary particle index (one-based) in the IPT block
   */
  bool isIsotropic( unsigned int particle ) const {

    return this->LXPN( particle ) == 0;
  }

  /**
   *  @brief Return whether or not the incident particle outgoing angular distribution is isotropic 
   *
   */
  bool incidentIsotropic( ) const {

    return this->LXPN1() == 0;
  }





  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using XPNL = XPNLocatorBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
