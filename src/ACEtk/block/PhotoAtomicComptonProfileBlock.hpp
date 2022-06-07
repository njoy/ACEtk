#ifndef NJOY_ACETK_BLOCK_PhotoAtomicComptonProfileBlock
#define NJOY_ACETK_BLOCK_PhotoAtomicComptonProfileBlock

// system includes

// other includes
#include "ACEtk/block/details/BaseBlockWithLocators.hpp"
#include "ACEtk/block/PhotoAtomicComptonProfile.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic LSWD and SWD block with the compton profile data
 *
 *  The PhotoAtomicComptonProfileBlock class contains NXS(5) sets of compton
 *  profiles, one for each electron shell.
 */
class PhotoAtomicComptonProfileBlock :
    protected details::BaseBlockWithLocators< PhotoAtomicComptonProfileBlock,
                                              PhotoAtomicComptonProfile > {

  friend class details::BaseBlockWithLocators< PhotoAtomicComptonProfileBlock,
                                               PhotoAtomicComptonProfile >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/PhotoAtomicComptonProfileBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int NSH() const { return BaseBlockWithLocators::NR(); }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronShells() const {

    return BaseBlockWithLocators::numberReactions();
  }

  /**
   *  @brief Return the relative compton profile locator for a shell index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LSWD( std::size_t index ) const {

    return BaseBlockWithLocators::LLOC( index );
  }

  /**
   *  @brief Return the relative compton profile locator for a shell index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t comptonProfileLocator( std::size_t index ) const {

    return BaseBlockWithLocators::locator( index );
  }

  /**
   *  @brief Return all compton profiles
   */
  const std::vector< PhotoAtomicComptonProfile >& data() const {

    return BaseBlockWithLocators::data();
  }

  /**
   *  @brief Return the compton profile for a shell index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const PhotoAtomicComptonProfile& comptonProfile( std::size_t index ) const {

    return BaseBlockWithLocators::data( index );
  }

  using BaseBlockWithLocators::empty;
  using BaseBlockWithLocators::name;
  using BaseBlockWithLocators::length;
  using BaseBlockWithLocators::XSS;
  using BaseBlockWithLocators::begin;
  using BaseBlockWithLocators::end;
};

using SWD = PhotoAtomicComptonProfileBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
