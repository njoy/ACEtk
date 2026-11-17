#ifndef NJOY_ACETK_CONTINUOUS_CROSSSECTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_CROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/BlockWithLocators.hpp"
#include "ACEtk/continuous/CrossSectionData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy LSIG and SIG block with the cross section data
 *
 *  The CrossSectionBlock class contains NXS(4) sets of cross section values,
 *  one for each reaction number on the MTR block. The order of these cross
 *  section data sets is the same as the order of the reaction numbers in the
 *  MTR block.
 */
class CrossSectionBlock :
    protected base::BlockWithLocators< CrossSectionBlock, CrossSectionData > {

  friend class base::BlockWithLocators< CrossSectionBlock, CrossSectionData >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  CrossSectionBlock() = default;

  CrossSectionBlock( const CrossSectionBlock& ) = default;
  CrossSectionBlock( CrossSectionBlock&& ) = default;

  CrossSectionBlock& operator=( const CrossSectionBlock& ) = default;
  CrossSectionBlock& operator=( CrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] xs    the cross section data
   */
  CrossSectionBlock( std::vector< CrossSectionData > xs ) :
    BlockWithLocators( "SIG", std::move( xs ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] lsig    the begin iterator of the LSIG block in the XSS array
   *  @param[in] sig     the begin iterator of the SIG block in the XSS array
   *  @param[in] end     the end iterator of the SIG block in the XSS array
   *  @param[in] ntr     the number of reactions (excluding elastic)
   */
  CrossSectionBlock( Iterator lsig, Iterator sig, Iterator end, unsigned int ntr ) :
    BlockWithLocators( "SIG", lsig, sig, end, ntr ) {}

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return BlockWithLocators::N(); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const {

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
  const std::vector< CrossSectionData >& data() const {

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
  const CrossSectionData& crossSectionData( std::size_t index ) const {

    return BlockWithLocators::data( index );
  }

  /**
   *  @brief Return the energy index for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t energyIndex( std::size_t index ) const {

    return this->crossSectionData( index ).energyIndex();
  }

  /**
   *  @brief Return the number of cross section values for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t numberValues( std::size_t index ) const {

    return this->crossSectionData( index ).numberValues();
  }

  /**
   *  @brief Return the cross section values for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  auto crossSections( std::size_t index ) const {

    return this->crossSectionData( index ).crossSections();
  }

  using BlockWithLocators::empty;
  using BlockWithLocators::name;
  using BlockWithLocators::length;
  using BlockWithLocators::XSS;
  using BlockWithLocators::begin;
  using BlockWithLocators::end;
};

using SIG = CrossSectionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
