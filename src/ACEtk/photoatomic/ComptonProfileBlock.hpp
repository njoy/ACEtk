#ifndef NJOY_ACETK_PHOTOATOMIC_COMPTONPROFILEBLOCK
#define NJOY_ACETK_PHOTOATOMIC_COMPTONPROFILEBLOCK

// system includes

// other includes
#include "ACEtk/base/BaseBlockWithLocators.hpp"
#include "ACEtk/photoatomic/ComptonProfile.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic LSWD and SWD block with the compton profile data
 *
 *  The ComptonProfileBlock class contains NXS(5) sets of compton
 *  profiles, one for each electron shell.
 */
class ComptonProfileBlock :
    protected base::BaseBlockWithLocators< ComptonProfileBlock,
                                           ComptonProfile > {

  friend class base::BaseBlockWithLocators< ComptonProfileBlock,
                                            ComptonProfile >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/photoatomic/ComptonProfileBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int NSH() const { return BaseBlockWithLocators::N(); }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronShells() const {

    return BaseBlockWithLocators::numberDataBlocks();
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
  const std::vector< ComptonProfile >& data() const {

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
  const ComptonProfile& comptonProfile( std::size_t index ) const {

    return BaseBlockWithLocators::data( index );
  }

  using BaseBlockWithLocators::empty;
  using BaseBlockWithLocators::name;
  using BaseBlockWithLocators::length;
  using BaseBlockWithLocators::XSS;
  using BaseBlockWithLocators::begin;
  using BaseBlockWithLocators::end;
};

using SWD = ComptonProfileBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
