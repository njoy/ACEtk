#ifndef NJOY_ACETK_BLOCK_FISSIONMULTIPLICITYBLOCK
#define NJOY_ACETK_BLOCK_FISSIONMULTIPLICITYBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/PolynomialFissionMultiplicity.hpp"
#include "ACEtk/block/TabulatedFissionMultiplicity.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy NU block with the fission multiplicity data
 */
class FissionMultiplicityBlock : protected details::Base {

public:

  /* type aliases */
  using FissionMultiplicityData = std::variant< PolynomialFissionMultiplicity,
                                                TabulatedFissionMultiplicity >;

private:

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/FissionMultiplicityBlock/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/FissionMultiplicityBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return whether or not prompt and total fission multiplicity are
   *         present
   */
  bool hasPromptAndTotalFissionMultiplicity() const {

    return this->XSS( 1 ) < 0;
  }

  /**
   *  @brief Return the prompt fission multiplicity
   *
   *  This returns the prompt fission multiplicity when both prompt and total
   *  are given or just the available multiplicity data if only one of these is
   *  given (the ACE format does not indicate which is present).
   */
  FissionMultiplicityData promptFissionMultiplicity() const {

    Iterator begin = this->begin();
    Iterator end = this->end();

    if ( this->hasPromptAndTotalFissionMultiplicity() ) {

      auto knu = static_cast<unsigned int>( std::abs( round( *begin ) ) ) + 1;
      end = std::next( begin, knu );
      begin = std::next( begin );
    }

    unsigned int LNU = static_cast< unsigned int >( round( *begin ) );
    switch (LNU) {

      case 1: return PolynomialFissionMultiplicity( begin, end );
      case 2: return TabulatedFissionMultiplicity( begin, end );
      default: {

        Log::error( "Illegal fission multiplicity representation LNU = {}", LNU );
        Log::info( "Only LNU = 1 (polynomial) or LNU = 2 (tabulated) are allowed" );
        throw std::exception();
      }
    }
  }

  /**
   *  @brief Return the total fission multiplicity
   *
   *  This returns the total fission multiplicity when both prompt and total
   *  are given or just the available multiplicity data if only one of these is
   *  given (the ACE format does not indicate which is present).
   */
  FissionMultiplicityData totalFissionMultiplicity() const {

    Iterator begin = this->begin();
    Iterator end = this->end();

    if ( this->hasPromptAndTotalFissionMultiplicity() ) {

      auto knu = static_cast<unsigned int>( std::abs( round( *begin ) ) ) + 1;
      begin = std::next( begin, knu );
    }

    unsigned int LNU = static_cast< unsigned int >( round( *begin ) );
    switch (LNU) {

      case 1: return PolynomialFissionMultiplicity( begin, end );
      case 2: return TabulatedFissionMultiplicity( begin, end );
      default: {

        Log::error( "Illegal fission multiplicity representation LNU = {}", LNU );
        Log::info( "Only LNU = 1 (polynomial) or LNU = 2 (tabulated) are allowed" );
        throw std::exception();
      }
    }
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using NU = FissionMultiplicityBlock;
using DNU = FissionMultiplicityBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
