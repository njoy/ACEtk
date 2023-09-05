#ifndef NJOY_ACETK_BLOCK_DOSIMETRYCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_DOSIMETRYCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/BaseBlockWithLocators.hpp"
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
    protected details::BaseBlockWithLocators< DosimetryCrossSectionBlock,
                                              DosimetryCrossSectionData > {

  friend class details::BaseBlockWithLocators< DosimetryCrossSectionBlock,
                                               DosimetryCrossSectionData >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/DosimetryCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available reactions
   */
  unsigned int NTR() const { return BaseBlockWithLocators::N(); }

  /**
   *  @brief Return the number of available reactions
   */
  unsigned int numberReactions() const {

    return BaseBlockWithLocators::numberDataBlocks();
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
   *  @brief Return all cross section data
   */
  const std::vector< DosimetryCrossSectionData >& data() const {

    return BaseBlockWithLocators::data();
  }

  /**
   *  @brief Return the cross section data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DosimetryCrossSectionData& crossSectionData( std::size_t index ) const {

    return BaseBlockWithLocators::data( index );
  }

  using BaseBlockWithLocators::empty;
  using BaseBlockWithLocators::name;
  using BaseBlockWithLocators::length;
  using BaseBlockWithLocators::XSS;
  using BaseBlockWithLocators::begin;
  using BaseBlockWithLocators::end;
};

using SIGD = DosimetryCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
