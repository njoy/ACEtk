#ifndef NJOY_ACETK_BLOCK_PHOTOATOMICSUBSHELLTRANSITIONDATABLOCK
#define NJOY_ACETK_BLOCK_PHOTOATOMICSUBSHELLTRANSITIONDATABLOCK

// system includes

// other includes
#include "ACEtk/block/details/BaseBlockWithLocators.hpp"
#include "ACEtk/block/PhotoatomicSubshellTransitionData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic and electron RELO and XPROB block with the transition data
 *
 *  The PhotoatomicSubshellTransitionDataBlock class contains the transition
 *  data for each subshell (the number of subshells NSSH is stored in NXS(7)).
 */
class PhotoatomicSubshellTransitionDataBlock :
    protected details::BaseBlockWithLocators< PhotoatomicSubshellTransitionDataBlock,
                                              PhotoatomicSubshellTransitionData > {

  friend class details::BaseBlockWithLocators< PhotoatomicSubshellTransitionDataBlock,
                                               PhotoatomicSubshellTransitionData >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/PhotoatomicSubshellTransitionDataBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of electron subshells
   */
  unsigned int NSSH() const { return this->N(); }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronSubshells() const { return this->NSSH(); }

  /**
   *  @brief Return the relative transition data locator for a subshell index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LTRAN( std::size_t index ) const {

    return BaseBlockWithLocators::LLOC( index );
  }

  /**
   *  @brief Return the relative transition data locator for a subshell index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t transitionDataLocator( std::size_t index ) const {

    return BaseBlockWithLocators::locator( index );
  }

  /**
   *  @brief Return all transition data
   */
  const std::vector< PhotoatomicSubshellTransitionData >& data() const {

    return BaseBlockWithLocators::data();
  }

  /**
   *  @brief Return the transition data for a subshell index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const PhotoatomicSubshellTransitionData& transitionData( std::size_t index ) const {

    return BaseBlockWithLocators::data( index );
  }

  using BaseBlockWithLocators::empty;
  using BaseBlockWithLocators::name;
  using BaseBlockWithLocators::length;
  using BaseBlockWithLocators::XSS;
  using BaseBlockWithLocators::begin;
  using BaseBlockWithLocators::end;
};

using XPROB = PhotoatomicSubshellTransitionDataBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
