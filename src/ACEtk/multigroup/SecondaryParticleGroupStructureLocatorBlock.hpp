#ifndef NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLEGROUPSTRUCTURELOCATORBLOCK
#define NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLEGROUPSTRUCTURELOCATORBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup ERG2L block with locators for the group structure block(s)
 *         for the secondary particle(s)
 *
 *  The SecondaryParticleGroupStructureLocatorBlock class contains NSEC locators, one 
 *  for each secondary particle type given in the IPT block.
 *
 *  The number of secondary particles is stored in NXS(8).
 */
class SecondaryParticleGroupStructureLocatorBlock : protected base::Base {

  /* fields */

  unsigned int nsec_ = 0;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( std::vector< unsigned int >&& locators ) {

    std::vector< double > xss;
    const auto nsec = locators.size();
    xss.reserve( nsec );
    xss.insert( xss.end(), locators.begin(), locators.end() );
    return xss;
  }

  static void verifySize( Iterator begin, Iterator end, unsigned int nsec ) {

    auto size = std::distance( begin, end );
    if ( size < 1 * nsec ) {

      Log::error( "The size of the XSS subrange should be at least 1 * NSEC" );
      Log::info( "NSEC value: {}", nsec );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  SecondaryParticleGroupStructureLocatorBlock(
      std::vector< unsigned int > && locators,
      std::size_t nsec ) :
    Base( "ERG2L", generateXSS( std::move( locators ) ) ),
    nsec_( nsec ) {}

public:

  /* constructor */

  SecondaryParticleGroupStructureLocatorBlock() = default;

  SecondaryParticleGroupStructureLocatorBlock( const SecondaryParticleGroupStructureLocatorBlock& ) = default;
  SecondaryParticleGroupStructureLocatorBlock( SecondaryParticleGroupStructureLocatorBlock&& ) = default;

  SecondaryParticleGroupStructureLocatorBlock& operator=( const SecondaryParticleGroupStructureLocatorBlock& ) = default;
  SecondaryParticleGroupStructureLocatorBlock& operator=( SecondaryParticleGroupStructureLocatorBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] locators    the locators for each secondary particle type
   */
  SecondaryParticleGroupStructureLocatorBlock(
      std::vector< unsigned int > locators ) :
    SecondaryParticleGroupStructureLocatorBlock( std::move( locators ), locators.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] erg2l     the begin iterator of the ERG2L block in the XSS array
   *  @param[in] end       the end iterator of the ERG2L block in the XSS array
   *  @param[in] nsec      the number of secondary particle types
   */
  SecondaryParticleGroupStructureLocatorBlock( Iterator erg2l, Iterator end, unsigned int nsec ) :
    Base( "ERG2L", erg2l, end ), nsec_( nsec ) {

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
   *  @brief Return the locator for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based)
   */
  std::size_t ERG2( std::size_t particle ) const {

    return this->IXSS( particle );
  }

  /**
   *  @brief Return the locator for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based)
   */
  std::size_t locator( std::size_t particle ) const {

    return this->ERG2( particle );
  }



  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ERG2L = SecondaryParticleGroupStructureLocatorBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
