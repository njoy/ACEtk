#ifndef NJOY_ACETK_BLOCK_SECONDARYPARTICLETYPEBLOCK
#define NJOY_ACETK_BLOCK_SECONDARYPARTICLETYPEBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy PTYPE block with the secondary particle types
 *
 *  The SecondaryParticleTypeBlock class contains the secondary particle types
 *  for which data is available (excluding the incident particle type).
 *
 *  The number of available particle types is stored in NXS(7).
 */
class SecondaryParticleTypeBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/SecondaryParticleTypeBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile)
   */
  unsigned int NTYPE() const { return this->N(); }

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile)
   */
  unsigned int numberAdditionalSecondaryParticleTypes() const {

    return this->NTYPE();
  }

  /**
   *  @brief Return the particle type for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int IP( std::size_t index ) const { return this->ivalue( 1, index ); }

  /**
   *  @brief Return the particle type for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int particleType( std::size_t index ) const {

    return this->IP( index );
  }

  /**
   *  @brief Return the particle types
   */
  auto IPs() const { return this->iarray( 1 ); }

  /**
   *  @brief Return the particle types
   */
  auto particleTypes() const { return this->IPs(); }

  /**
   *  @brief Return whether or not the particle type is present
   *
   *  @param[in] type    the particle type
   */
  bool hasIP( unsigned int type ) const {

    return std::find_if(
               this->begin(),
               this->begin() + this->NTYPE(),
               [type] ( auto&& value ) {

                 return static_cast< unsigned int >( std::round( value ) )
                        == type;
               } ) != this->end();
  }

  /**
   *  @brief Return whether or not the particle type is present
   *
   *  @param[in] type    the particle type
   */
  bool hasParticleType( unsigned int reaction ) const {

    return this->hasIP( reaction );
  }

  /**
   *  @brief Return the index (one-based) of the particle type
   *
   *  @param[in] type    the particle type
   */
  std::size_t index( unsigned int type ) const {

    auto iter = std::find_if(
                    this->begin(), this->begin() + this->NTYPE(),
                    [type] ( auto&& value ) {

                      return static_cast< unsigned int >( std::round( value ) )
                             == type;
                    } );
    if ( iter != this->end() ) {

      return std::distance( this->begin(), iter ) + 1;
    }
    else {

      Log::error( "The requested particle type IP{} is not present", type );
      throw std::exception();
    }
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using PTYPE = SecondaryParticleTypeBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
