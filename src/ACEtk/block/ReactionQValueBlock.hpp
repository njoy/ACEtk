#ifndef NJOY_ACETK_BLOCK_REACTIONQVALUEBLOCK
#define NJOY_ACETK_BLOCK_REACTIONQVALUEBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy LQR block with the reaction Q values
 *
 *  The ReactionQValueBlock class contains the reaction Q values for all
 *  available reactions (excluding elastic). The order of these Q values
 *  is the same as the order of the reaction numbers in the MTR block.
 *
 *  The number of available reactions (excluding elastic) is stored in NXS(4).
 */
class ReactionQValueBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/ReactionQValueBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return this->N(); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const { return this->NTR(); }

  /**
   *  @brief Return the Q value for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  double QValue( std::size_t index ) const { return this->dvalue( 1, index ); }

  /**
   *  @brief Return the Q values
   */
  auto QValues() const { return this->darray( 1 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using LQR = ReactionQValueBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
