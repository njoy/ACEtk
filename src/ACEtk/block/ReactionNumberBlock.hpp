#ifndef NJOY_ACETK_BLOCK_REACTIONNUMBERBLOCK
#define NJOY_ACETK_BLOCK_REACTIONNUMBERBLOCK

// system includes

// other includes
#include "ACEtk/block/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy MTR block with the reaction MT numbers
 *
 *  The ReactionNumberBlock class contains the reaction MT numbers for all
 *  available reactions (excluding elastic)
 *
 *  The number of available reactions (excluding elastic) is stored in NXS(4).
 */
class ReactionNumberBlock : protected Base {

  /* fields */
  unsigned int ntr_;

  /* auxiliary functions */
  #include "ACEtk/block/ReactionNumberBlock/src/generateXSS.hpp"
  #include "ACEtk/block/ReactionNumberBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/ReactionNumberBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return this->ntr_; }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const { return this->NTR(); }

  /**
   *  @brief Return the reaction numbers
   */
  auto mts() const { return this->XSS( 1, this->NTR() ); }

  using Base::name;
  using Base::length;
  using Base::XSS;
};

using MTR = ReactionNumberBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
