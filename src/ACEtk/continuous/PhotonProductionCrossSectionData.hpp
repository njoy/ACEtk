#ifndef NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONCROSSSECTIONDATA
#define NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONCROSSSECTIONDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Secondary particle production cross section data from the SIGP block
 *         for a single reaction
 */
class PhotonProductionCrossSectionData : protected base::Base {

  /* fields */

  /* auxiliary functions */

  static std::vector< double > generateXSS(
      std::size_t index,
      std::vector< double >&& values ) {

    std::vector< double > xss = { 13.,
                                  static_cast< double >( index ),
                                  static_cast< double >( values.size() ) };
    xss.reserve( 3 + values.size() );
    xss.insert( xss.end(), values.begin(), values.end() );

    return xss;
  }

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int numberValues ) {

    auto size = std::distance( begin, end );
    if ( size < numberValues + 3 ) {

      Log::error( "The size of the XSS subrange in the production cross section "
                  "data should be at least 3 + XSS(3)" );
      Log::info( "XSS(3) value: {}", numberValues );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

public:

  /* constructor */

  PhotonProductionCrossSectionData() = default;

  PhotonProductionCrossSectionData( const PhotonProductionCrossSectionData& ) = default;
  PhotonProductionCrossSectionData( PhotonProductionCrossSectionData&& ) = default;

  PhotonProductionCrossSectionData& operator=( const PhotonProductionCrossSectionData& ) = default;
  PhotonProductionCrossSectionData& operator=( PhotonProductionCrossSectionData&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] index     the energy index
   *  @param[in] values    the cross section values
   */
  PhotonProductionCrossSectionData( std::size_t index,
                                    std::vector< double > values ) :
    Base( "PhotonProductionCrossSectionData",
          generateXSS( index, std::move( values ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the cross section data
   *  @param[in] end      the end iterator of the cross section data
   */
  PhotonProductionCrossSectionData( Iterator begin, Iterator end ) :
    Base( "PhotonProductionCrossSectionData", begin, end ) {

    verifySize( this->begin(), this->end(), this->numberValues() );
  }

  /**
   *  @brief Return the representation type (should always be 13)
   */
  unsigned int MFTYPE() const {

    return static_cast< unsigned int >( this->IXSS( 1 ) );
  }

  /**
   *  @brief Return the representation type (should always be 13)
   */
  unsigned int type() const { return this->MFTYPE(); }

  /**
   *  @brief Return the energy index
   */
  std::size_t energyIndex() const { return this->IXSS( 2 ); }

  /**
   *  @brief Return the number of cross section values
   */
  std::size_t numberValues() const { return this->XSS( 3 ); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const { return this->XSS( 4, this->numberValues() ); }

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
