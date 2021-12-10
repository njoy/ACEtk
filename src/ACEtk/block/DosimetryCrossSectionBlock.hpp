#ifndef NJOY_ACETK_BLOCK_DOSIMETRYCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_DOSIMETRYCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/BaseCrossSectionBlock.hpp"
#include "ACEtk/block/DosimetryCrossSectionData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy LSIG and SIGD block with the dosimetry cross
 *         section data
 *
 *  The CrossSectionBlock class contains NXS(4) sets of dosimetry cross section
 *  data sets, one for each reaction number on the MTR block. The order of these
 *  cross section data sets is the same as the order of the reaction numbers in
 *  the MTR block.
 */
class DosimetryCrossSectionBlock :
    protected details::BaseCrossSectionBlock< DosimetryCrossSectionBlock,
                                              DosimetryCrossSectionData > {

  friend class details::BaseCrossSectionBlock< DosimetryCrossSectionBlock,
                                               DosimetryCrossSectionData >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/DosimetryCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return BaseCrossSectionBlock::NTR(); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const {

    return BaseCrossSectionBlock::numberReactions();
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

    return BaseCrossSectionBlock::LSIG( index );
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

    return BaseCrossSectionBlock::crossSectionLocator( index );
  }

  /**
   *  @brief Return the cross section data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  auto crossSectionData( std::size_t index ) const {

    return BaseCrossSectionBlock::crossSectionData( index );
  }

  using BaseCrossSectionBlock::empty;
  using BaseCrossSectionBlock::name;
  using BaseCrossSectionBlock::length;
  using BaseCrossSectionBlock::XSS;
  using BaseCrossSectionBlock::begin;
  using BaseCrossSectionBlock::end;
};

using SIGD = DosimetryCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
