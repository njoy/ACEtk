#ifndef NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONCROSSSECTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONCROSSSECTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/base/BlockWithLocators.hpp"
#include "ACEtk/continuous/PhotonProductionCrossSectionData.hpp"
#include "ACEtk/continuous/TabulatedSecondaryParticleMultiplicity.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/* type alias */

using PhotonProductionData = std::variant<
                                 PhotonProductionCrossSectionData,
                                 TabulatedSecondaryParticleMultiplicity >;

/**
 *  @class
 *  @brief The continuous energy LSIGP and SIGP block with the photon
 *         production cross section data
 *
 *  The PhotonProductionCrossSectionBlock class contains NXS(6) sets of photon
 *  production data, one for each reaction number on the MTRP block. The order
 *  of these cross section data sets is the same as the order of the reaction
 *  numbers in the MTRP block.
 */
class PhotonProductionCrossSectionBlock :
    protected base::BlockWithLocators< PhotonProductionCrossSectionBlock,
                                       PhotonProductionData > {

  friend class base::BlockWithLocators< PhotonProductionCrossSectionBlock,
                                        PhotonProductionData >;

  /* fields */

  /* auxiliary functions */

  static std::vector< double > generateXSS( std::vector< PhotonProductionData >&& xs, bool ) {

    const auto ntr = xs.size();
    std::vector< double > xss( ntr );
    std::size_t index = 0;
    for ( const auto& data : xs ) {

      xss[index] = xss.size() - ntr + 1;
      std::visit( [&xss] ( const auto& value )
                         { xss.insert( xss.end(), value.begin(), value.end() ); },
                   data );
      ++index;
    }

    return xss;
  }

  static PhotonProductionData
  generateData( std::size_t, Iterator left, Iterator right ) {

    if ( static_cast< int >( std::round( *left ) ) == 13 ) {

      return PhotonProductionCrossSectionData( left, right );
    }
    else {

      return TabulatedSecondaryParticleMultiplicity( left, right );
    }
  }

public:

  /* constructor */

  PhotonProductionCrossSectionBlock() = default;

  PhotonProductionCrossSectionBlock( const PhotonProductionCrossSectionBlock& ) = default;
  PhotonProductionCrossSectionBlock( PhotonProductionCrossSectionBlock&& ) = default;

  PhotonProductionCrossSectionBlock& operator=( const PhotonProductionCrossSectionBlock& ) = default;
  PhotonProductionCrossSectionBlock& operator=( PhotonProductionCrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] xs    the cross section data
   */
  PhotonProductionCrossSectionBlock( std::vector< PhotonProductionData > xs ) :
    BlockWithLocators( "SIGP", std::move( xs ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] lsigp    the begin iterator of the LSIGP block in the XSS array
   *  @param[in] sigp     the begin iterator of the SIGP block in the XSS array
   *  @param[in] end      the end iterator of the SIGP block in the XSS array
   *  @param[in] ntr      the number of reactions
   */
  PhotonProductionCrossSectionBlock( Iterator lsigp, Iterator sigp, Iterator end,
                                     unsigned int ntr ) :
    BlockWithLocators( "SIGP", lsigp, sigp, end, ntr ) {}

  /* methods */

  /**
   *  @brief Return the number of photon production reactions
   */
  unsigned int NTRP() const { return BlockWithLocators::N(); }

  /**
   *  @brief Return the number of photon production reactions
   */
  unsigned int numberPhotonProductionReactions() const {

    return BlockWithLocators::numberDataBlocks();
  }

  /**
   *  @brief Return the relative cross section locator for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LSIG( std::size_t index ) const {

    return BlockWithLocators::LLOC( index );
  }

  /**
   *  @brief Return the relative cross section locator for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t crossSectionLocator( std::size_t index ) const {

    return BlockWithLocators::locator( index );
  }

  /**
   *  @brief Return all cross section data
   */
  const std::vector< PhotonProductionData >& data() const {

    return BlockWithLocators::data();
  }

  /**
   *  @brief Return the cross section data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const PhotonProductionData& crossSectionData( std::size_t index ) const {

    return BlockWithLocators::data( index );
  }

  using BlockWithLocators::empty;
  using BlockWithLocators::name;
  using BlockWithLocators::length;
  using BlockWithLocators::XSS;
  using BlockWithLocators::begin;
  using BlockWithLocators::end;
};

using SIGP = PhotonProductionCrossSectionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
