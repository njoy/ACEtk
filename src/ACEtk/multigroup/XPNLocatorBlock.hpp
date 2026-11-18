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

  static std::vector< double >
  generateXSS( std::vector< unsigned int >&& locators ) {

    std::vector< double > xss;
    const auto nsec = locators.size() - 1;
    xss.reserve( nsec + 1 );
    xss.insert( xss.end(), locators.begin(), locators.end() );
    return xss;
  }

  static void verifySize( Iterator begin, Iterator end, unsigned int nsec ) {

    auto size = std::distance( begin, end );
    if ( size != 1 + nsec ) {

      Log::error( "The size of the XSS subrange should be NSEC + 1" );
      Log::info( "NSEC value: {}", nsec );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  XPNLocatorBlock(
      std::vector< unsigned int > && locators,
      std::size_t nsec ) :
    Base( "XPNL", generateXSS( std::move( locators ) ) ),
    nsec_( nsec ) {}

public:

  /* constructor */

  XPNLocatorBlock() = default;

  XPNLocatorBlock( const XPNLocatorBlock& ) = default;
  XPNLocatorBlock( XPNLocatorBlock&& ) = default;

  XPNLocatorBlock& operator=( const XPNLocatorBlock& ) = default;
  XPNLocatorBlock& operator=( XPNLocatorBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] locators    the locators for each XPN block
   */
  XPNLocatorBlock(
      std::vector< unsigned int > locators ) :
    XPNLocatorBlock( std::move( locators ), locators.size() - 1 ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin     the begin iterator of the XPNL block in the XSS array
   *  @param[in] end       the end iterator of the XPNL block in the XSS array
   *  @param[in] nsec      the number of secondary particle types
   */
  XPNLocatorBlock( Iterator begin, Iterator end, unsigned int nsec ) :
    Base( "XPNL", begin, end ), nsec_( nsec ) {

    verifySize( this->begin(), this->end(), this->NSEC() );
  }

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
