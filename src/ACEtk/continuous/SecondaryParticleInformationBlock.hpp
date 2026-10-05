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

  static std::vector< double > generateXSS( std::vector< unsigned int >&& numbers ) {

    std::vector< double > xss;
    const auto ntype = numbers.size();
    xss.reserve( ntype );
    xss.insert( xss.end(), numbers.begin(), numbers.end() );
    return xss;
  }

  static void verifySize( Iterator begin, Iterator end, unsigned int ntype ) {

    auto size = std::distance( begin, end );
    if ( size < ntype ) {

      Log::error( "The size of the XSS subrange should be at least NTYPE" );
      Log::info( "NTYPE value: {}", ntype );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  SecondaryParticleInformationBlock( std::vector< unsigned int >&& numbers,
                                     std::size_t ntype ) :
    Base( "NTRO", generateXSS( std::move( numbers ) ) ),
    ntype_( ntype ) {}

public:

  /* constructor */

  SecondaryParticleInformationBlock() = default;

  SecondaryParticleInformationBlock( const SecondaryParticleInformationBlock& ) = default;
  SecondaryParticleInformationBlock( SecondaryParticleInformationBlock&& ) = default;

  SecondaryParticleInformationBlock& operator=( const SecondaryParticleInformationBlock& ) = default;
  SecondaryParticleInformationBlock& operator=( SecondaryParticleInformationBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] numbers    the number of reactions for each secondary particle type
   */
  SecondaryParticleInformationBlock( std::vector< unsigned int > numbers ) :
    SecondaryParticleInformationBlock( std::move( numbers ), numbers.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] ntro    the begin iterator of the NTRO block in the XSS array
   *  @param[in] end     the end iterator of the NTRO block in the XSS array
   *  @param[in] ntype   the number of secondary particle types
   */
  SecondaryParticleInformationBlock( Iterator ntro, Iterator end, unsigned int ntype ) :
    Base( "NTRO", ntro, end ), ntype_( ntype ) {

    verifySize( this->begin(), this->end(), this->NTYPE() );
  }

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
