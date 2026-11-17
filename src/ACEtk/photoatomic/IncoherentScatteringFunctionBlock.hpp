#ifndef NJOY_ACETK_PHOTOATOMIC_INCOHERENTSCATTERINGFUNCTIONBLOCK
#define NJOY_ACETK_PHOTOATOMIC_INCOHERENTSCATTERINGFUNCTIONBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/ArrayData.hpp"
#include "tools/std20/views.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic JINC block with the incoherent scattering function
 *
 *  The IncoherentScatteringFunctionBlock class contains one of the following
 *  representations of the scattering function:
 *    - 21 scattering function values using a fixed momentum grid (mcplib version)
 *    - tabulated momentum and scattering function values (eprdata version)
 *
 *  The interface abstracts away the distinction between the two representations.
 *
 *  The recoil electron momentum transfer values are given in inverse angstroms.
 */
class IncoherentScatteringFunctionBlock : protected base::ArrayData {

  /* fields */

  std::optional< std::vector< double > > momentum_;

  /* auxiliary functions */

  static unsigned int numberElements( Iterator begin, Iterator end ) {

    auto size = std::distance( begin, end );
    if ( 21 == size ) {

      return 21;
    }
    else {

      if ( 0 != size % 2 ) {

        Log::error( "The size of the XSS subrange in the JINC block for an "
                    "arbitrarily tabulated scattering function should be even" );
        Log::info( "XSS.size(): {}", size );
        throw std::exception();
      }
      return size / 2;
    }
  }

  static unsigned int numberArrays( Iterator begin, Iterator end ) {

    return std::distance( begin, end ) == 21 ? 1 : 2;
  }

  static std::vector< std::vector< double > > 
  generateArrays( std::vector< double > values ) {

    if ( 21 != values.size() ) {

      Log::error( "The size of the XSS subrange in the JINC block for an "
                  "mcplib style scattering function should be 21" );
      Log::info( "XSS.size(): {}", values.size() );
      throw std::exception();
    }
    return { std::move( values ) };
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  IncoherentScatteringFunctionBlock( Iterator begin, Iterator end,
                                     unsigned int size,
                                     unsigned int n, unsigned int m ) :
    ArrayData( "JINC", begin, end, n, m ), momentum_( std::nullopt ) {

    if ( size == 21 ) {

      momentum_ = {{ 0., .005, .01, .05, .1, .15, .2,
                     .3, .4, .5, .6, .7, .8, .9, 1., 1.5, 2., 3., 4., 5., 8. }};
    }
  }

public:

  /* constructor */

  IncoherentScatteringFunctionBlock() = default;

  IncoherentScatteringFunctionBlock( const IncoherentScatteringFunctionBlock& ) = default;
  IncoherentScatteringFunctionBlock( IncoherentScatteringFunctionBlock&& ) = default;

  IncoherentScatteringFunctionBlock& operator=( const IncoherentScatteringFunctionBlock& ) = default;
  IncoherentScatteringFunctionBlock& operator=( IncoherentScatteringFunctionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] values    the scattering function values
   */
  IncoherentScatteringFunctionBlock( std::vector< double > values ) :
    ArrayData( "JINC",
               generateArrays( std::move( values ) ) ) {

    momentum_ = {{ 0., .005, .01, .05, .1, .15, .2,
                   .3, .4, .5, .6, .7, .8, .9, 1., 1.5, 2., 3., 4., 5., 8. }};
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] momentum    the momentum values
   *  @param[in] values      the scattering function values
   */
  IncoherentScatteringFunctionBlock( std::vector< double > momentum,
                                     std::vector< double > values ) :
    ArrayData( "JINC", std::move( momentum ), std::move( values ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the JINC block in the XSS array
   *  @param[in] end     the end iterator of the JINC block in the XSS array
   */
  IncoherentScatteringFunctionBlock( Iterator begin, Iterator end ) :
    IncoherentScatteringFunctionBlock( begin, end,
                                       std::distance( begin, end ),
                                       numberElements( begin, end ),
                                       numberArrays( begin, end ) ) {}

  /* methods */

  /**
   *  @brief Return the number of values
   */
  unsigned int NM() const { return this->N(); }

  /**
   *  @brief Return the number of values
   */
  unsigned int numberValues() const { return NM(); }

  /**
   *  @brief Return the electron recoil momentum values
   */
  auto momentum() const {

    if ( this->momentum_.has_value() ) {

      return njoy::tools::std20::ranges::subrange( this->momentum_.value().begin(),
                                                   this->momentum_.value().end() );
    }
    else {

      return this->darray( 1 );
    }
  }

  /**
   *  @brief Return the scattering function values
   */
  auto values() const {

    return this->darray( this->momentum_.has_value() ? 1 : 2 );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using JINC = IncoherentScatteringFunctionBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
