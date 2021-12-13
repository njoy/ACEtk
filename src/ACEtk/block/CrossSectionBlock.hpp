#ifndef NJOY_ACETK_BLOCK_CROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_CROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/BaseBlockWithLocators.hpp"
#include "ACEtk/block/CrossSectionData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

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
    protected details::BaseBlockWithLocators< CrossSectionBlock,
                                              CrossSectionData > {

  friend class details::BaseBlockWithLocators< CrossSectionBlock,
                                               CrossSectionData >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/CrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return BaseBlockWithLocators::NR(); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const {

    return BaseBlockWithLocators::numberReactions();
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

    return BaseBlockWithLocators::LLOC( index );
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

    return BaseBlockWithLocators::locator( index );
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

    return BaseBlockWithLocators::data( index );
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

  using BaseBlockWithLocators::empty;
  using BaseBlockWithLocators::name;
  using BaseBlockWithLocators::length;
  using BaseBlockWithLocators::XSS;
  using BaseBlockWithLocators::begin;
  using BaseBlockWithLocators::end;
};

using SIG = CrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
