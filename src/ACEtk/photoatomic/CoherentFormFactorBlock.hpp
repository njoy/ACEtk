#ifndef NJOY_ACETK_PHOTOATOMIC_COHERENTFORMFACTORBLOCK
#define NJOY_ACETK_PHOTOATOMIC_COHERENTFORMFACTORBLOCK

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
 *  @brief The photoatomic JCOH block with the coherent form factors
 *
 *  The CoherentFormFactorBlock class contains one of the following
 *  representations of the form factor:
 *    - 55 values for the form factor and its integral form using a fixed
 *      momentum grid (mcplib version)
 *    - tabulated form factor and its integral form (eprdata version)
 */
class CoherentFormFactorBlock : protected base::ArrayData {

  /* fields */

  std::optional< std::vector< double > > momentum_;

  /* auxiliary functions */

  static unsigned int numberElements( Iterator begin, Iterator end ) {

    auto size = std::distance( begin, end );
    if ( 110 == size ) {

      return 55;
    }
    else {

      if ( 0 != size % 3 ) {

        Log::error( "The size of the XSS subrange in the JCOH block for"
                    "arbitrarily tabulated form factors should be a multiple of 3" );
        Log::info( "XSS.size(): {}", size );
        throw std::exception();
      }
      return size / 3;
    }
  }

  static unsigned int numberArrays( Iterator begin, Iterator end ) {

    return std::distance( begin, end ) == 110 ? 2 : 3;
  }

  static std::vector< std::vector< double > > 
  generateArrays( std::vector< double > integrated, std::vector< double > factors ) {

    if ( 110 != integrated.size() + factors.size() ) {

      Log::error( "The size of the XSS subrange in the JINC block for an "
                  "mcplib style form factors should be two times 55" );
      Log::info( "integrated form factors size(): {}", integrated.size() );
      Log::info( "form factors size(): {}", factors.size() );
      throw std::exception();
    }
    return { std::move( integrated ), std::move( factors ) };
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  CoherentFormFactorBlock( Iterator begin, Iterator end,
                           unsigned int size,
                           unsigned int n, unsigned int m ) :
    ArrayData( "JCOH", begin, end, n, m ), momentum_( std::nullopt ) {

    if ( size == 110 ) {

      momentum_ = {{ 0., .01, .02, .03, .04, .05, .06, .08, .10, .12, .15,
                    .18, .20, .25, .30, .35, .40, .45, .50, .55, .60, .70,
                    .80, .90, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8,
                    1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8,
                    4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0 }};
    }
  }

public:

  /* constructor */

  CoherentFormFactorBlock() = default;

  CoherentFormFactorBlock( const CoherentFormFactorBlock& ) = default;
  CoherentFormFactorBlock( CoherentFormFactorBlock&& ) = default;

  CoherentFormFactorBlock& operator=( const CoherentFormFactorBlock& ) = default;
  CoherentFormFactorBlock& operator=( CoherentFormFactorBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] integrated    the integrated form factor values
   *  @param[in] factors       the form factor values
   */
  CoherentFormFactorBlock( std::vector< double > integrated,
                           std::vector< double > factors ) :
    ArrayData( "JCOH",
               generateArrays( std::move( integrated ), std::move( factors ) ) ) {

    momentum_ = {{ 0., .01, .02, .03, .04, .05, .06, .08, .10, .12, .15,
                  .18, .20, .25, .30, .35, .40, .45, .50, .55, .60, .70,
                  .80, .90, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8,
                  1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8,
                  4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0 }};
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] momentum      the momentum values
   *  @param[in] integrated    the integrated form factor values
   *  @param[in] factors       the form factor values
   */
  CoherentFormFactorBlock( std::vector< double > momentum,
                           std::vector< double > integrated,
                           std::vector< double > factors ) :
    ArrayData( "JCOH", std::move( momentum ), std::move( integrated ),
                       std::move( factors ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the JINC block in the XSS array
   *  @param[in] end     the end iterator of the JINC block in the XSS array
   */
  CoherentFormFactorBlock( Iterator begin, Iterator end ) :
    CoherentFormFactorBlock( begin, end,
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
   *  @brief Return the integrated form factor values (tabulated on a grid of
   *         squared momentum values)
   */
  auto integratedFormFactors() const {

    return this->darray( this->momentum_.has_value() ? 1 : 2 );
  }

  /**
   *  @brief Return the form factor values (tabulated on a grid of momentum
   *         values)
   */
  auto formFactors() const {

    return this->darray( this->momentum_.has_value() ? 2 : 3 );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using JCOH = CoherentFormFactorBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
