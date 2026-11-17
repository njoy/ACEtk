#ifndef NJOY_ACETK_CONTINUOUS_CROSSSECTIONDATA
#define NJOY_ACETK_CONTINUOUS_CROSSSECTIONDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Cross section data from the SIG block for a single reaction
 *
 *  The CrossSectionData class contains the index of the energy point
 *  corresponding to the first cross section value, the number of cross
 *  section values and the actual cross section values.
 */
class CrossSectionData : protected base::Base {

  /* fields */

  /* auxiliary functions */

  static std::vector< double > generateXSS(
      std::size_t index,
      std::vector< double >&& values ) {

    std::vector< double > xss = { static_cast< double >( index ),
                                  static_cast< double >( values.size() ) };
    xss.reserve( 2 + values.size() );
    xss.insert( xss.end(), values.begin(), values.end() );

    return xss;
  }

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int numberValues ) {

    auto size = std::distance( begin, end );
    if ( size < numberValues + 2 ) {

      Log::error( "The size of the XSS subrange in the cross section data should "
                  "be at least 2 + XSS(2)" );
      Log::info( "XSS(2) value: {}", numberValues );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

public:

  /* constructor */

  CrossSectionData() = default;

  CrossSectionData( const CrossSectionData& ) = default;
  CrossSectionData( CrossSectionData&& ) = default;

  CrossSectionData& operator=( const CrossSectionData& ) = default;
  CrossSectionData& operator=( CrossSectionData&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] index     the energy index
   *  @param[in] values    the cross section values
   */
  CrossSectionData( std::size_t index, std::vector< double > values ) :
    Base( "CrossSectionData", generateXSS( index, std::move( values ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the cross section data
   *  @param[in] end      the end iterator of the cross section data
   */
  CrossSectionData( Iterator begin, Iterator end ) :
    Base( "CrossSectionData", begin, end ) {

    verifySize( this->begin(), this->end(), this->numberValues() );
  }

  /**
   *  @brief Return the energy index
   */
  std::size_t energyIndex() const { return this->IXSS( 1 ); }

  /**
   *  @brief Return the number of cross section values
   */
  std::size_t numberValues() const { return this->IXSS( 2 ); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const { return this->XSS( 3, this->numberValues() ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
