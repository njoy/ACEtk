#ifndef NJOY_ACETK_ELECTRON_SUBSHELLTRANSITIONDATABLOCK
#define NJOY_ACETK_ELECTRON_SUBSHELLTRANSITIONDATABLOCK

// system includes

// other includes
#include "ACEtk/base/BaseBlockWithLocators.hpp"
#include "ACEtk/electron/SubshellTransitionData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron RELO and XPROB block with the transition data
 *
 *  The SubshellTransitionDataBlock class contains the transition data for each
 *  subshell (the number of subshells NSSH is stored in NXS(7)).
 */
class SubshellTransitionDataBlock :
    protected base::BaseBlockWithLocators< SubshellTransitionDataBlock,
                                           SubshellTransitionData > {

  friend class base::BaseBlockWithLocators< SubshellTransitionDataBlock,
                                            SubshellTransitionData >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electron/SubshellTransitionDataBlock/src/ctor.hpp"

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
  const std::vector< SubshellTransitionData >& data() const {

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
  const SubshellTransitionData& transitionData( std::size_t index ) const {

    return BaseBlockWithLocators::data( index );
  }

  using BaseBlockWithLocators::empty;
  using BaseBlockWithLocators::name;
  using BaseBlockWithLocators::length;
  using BaseBlockWithLocators::XSS;
  using BaseBlockWithLocators::begin;
  using BaseBlockWithLocators::end;
};

using XPROB = SubshellTransitionDataBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
