#ifndef NJOY_ACETK_BLOCK_PRINCIPALCROSSSECTIONS
#define NJOY_ACETK_BLOCK_PRINCIPALCROSSSECTIONS

// system includes

// other includes
#include "ACEtk/block/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The ESZ block with the CE principal cross sections
 *
 *  The PrincipalCrossSectionBlock class contains 5 arrays of the same length:
 *    - the energy points
 *    - the total cross section
 *    - the elastic scattering cross section
 *    - the projectile disappearance cross section
 *    - the average heating numbers
 *
 *  The size of each (the total number of energy points) is stored in NXS(3)
 */
class PrincipalCrossSectionBlock : protected Base {

  /* fields */
  int nes_;

  /* auxiliary functions */
  auto subrange( unsigned int i ) const {

    const auto left = std::next( this->begin(), i * this->nes_ );
    const auto right = left + this->nes_;
    return ranges::make_iterator_range( left, right );
  }

  static std::vector< double > generateXSS(
      std::vector< double >&& energies,
      std::vector< double >&& total,
      std::vector< double >&& disappearance,
      std::vector< double >&& elastic,
      std::vector< double >&& heating ) {

    std::vector< double > xss( std::move( energies ) );
    auto nes = xss.size();
    xss.reserve( 5 * nes );

    if ( ( total.size() != nes ) || ( disappearance.size() != nes ) ||
         ( elastic.size() != nes ) || ( heating.size() != nes ) ) {

      Log::error( "The size of the ESZ subranges are not consistent" );
      Log::info( "NES value: {}", nes );
      Log::info( "energies.size(): {}", nes );
      Log::info( "total.size(): {}", total.size() );
      Log::info( "disappearance.size(): {}", disappearance.size() );
      Log::info( "elastic.size(): {}", elastic.size() );
      Log::info( "heating.size(): {}", heating.size() );
      throw std::exception();
    }

    xss.insert( xss.end(), total.begin(), total.end() );
    xss.insert( xss.end(), disappearance.begin(), disappearance.end() );
    xss.insert( xss.end(), elastic.begin(), elastic.end() );
    xss.insert( xss.end(), heating.begin(), heating.end() );

    return xss;
  }

  static void verifySize( Iterator begin, Iterator end, unsigned int nes ) {

    auto size = std::distance( begin, end );
    if ( size < 5 * nes ) {

      Log::error( "The size of the XSS subrange should be at least 5 * NES" );
      Log::info( "NES value: {}", nes );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

public:

  #include "ACEtk/block/PrincipalCrossSectionBlock/src/ctor.hpp"

  int NES() const { return this->nes_; }
  int numberEnergyPoints() const { return this->NES(); }

  auto energies() const { return this->subrange( 0 ); }
  auto total() const { return this->subrange( 1 ); }
  auto disappearance() const { return this->subrange( 2 ); }
  auto elastic() const { return this->subrange( 3 ); }
  auto heating() const { return this->subrange( 4 ); }
};

using ESZ = PrincipalCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
