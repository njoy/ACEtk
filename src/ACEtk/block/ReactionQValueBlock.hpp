#ifndef NJOY_ACETK_BLOCK_REACTIONQVALUEBLOCK
#define NJOY_ACETK_BLOCK_REACTIONQVALUEBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/block/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy LQR block with the reaction Q values
 *
 *  The ReactionQValueBlock class contains the reaction Q values for all
 *  available reactions (excluding elastic)
 *
 *  The number of available reactions (excluding elastic) is stored in NXS(4).
 */
class ReactionQValueBlock : protected Base {

  /* fields */
  unsigned int ntr_;

  /* auxiliary functions */
  #include "ACEtk/block/ReactionQValueBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/ReactionQValueBlock/src/ctor.hpp"

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
   *  @brief Return the Q value for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  auto QValue( std::size_t index ) const { return this->XSS( index ); }

  /**
   *  @brief Return the Q values
   */
  auto QValues() const { return this->XSS( 1, this->NTR() ); }

  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using LQR = ReactionQValueBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
