#ifndef NJOY_ACETK_BLOCK_FRAMEANDMULTIPLICITYBLOCK
#define NJOY_ACETK_BLOCK_FRAMEANDMULTIPLICITYBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/ReferenceFrame.hpp"
#include "range/v3/view/transform.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy TYR block with the outgoing projectile
 *         multiplicities and reference frames
 *
 *  The FrameAndMultiplicityBlock class contains the reference frame and
 *  outgoing projectile multiplicity. The order of this data is the same as
 *  the order of the reaction numbers in the MTR block.
 *
 *  The number of available reactions (excluding elastic) is stored in NXS(4).
 */
class FrameAndMultiplicityBlock : protected base::Base {

  /* fields */
  std::size_t ntr_ = 0;
  std::vector< ReferenceFrame > frames_;
  std::vector< unsigned int > multiplicities_;

  /* auxiliary functions */
  #include "ACEtk/block/FrameAndMultiplicityBlock/src/generateXSS.hpp"
  #include "ACEtk/block/FrameAndMultiplicityBlock/src/generateBlocks.hpp"
  #include "ACEtk/block/FrameAndMultiplicityBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/FrameAndMultiplicityBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  std::size_t NTR() const { return this->ntr_; }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  std::size_t numberReactions() const { return this->NTR(); }

  /**
   *  @brief Return the reference frame for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  const ReferenceFrame& referenceFrame( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyReactionIndex( index, 1, this->NTR() );
    #endif
    return this->frames_[ index - 1 ];
  }

  /**
   *  @brief Return the reference frames
   */
  const std::vector< ReferenceFrame >& referenceFrames() const {

    return this->frames_;
  }

  /**
   *  @brief Return the multiplicity value for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int multiplicity( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyReactionIndex( index, 1, this->NTR() );
    #endif
    return this->multiplicities_[ index - 1 ];
  }

  /**
   *  @brief Return the multiplicities
   */
  const std::vector< unsigned int >& multiplicities() const {

    return this->multiplicities_;
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using TYR = FrameAndMultiplicityBlock;
using TYRH = FrameAndMultiplicityBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
