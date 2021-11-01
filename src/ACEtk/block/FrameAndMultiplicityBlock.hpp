#ifndef NJOY_ACETK_BLOCK_FRAMEANDMULTIPLICITYBLOCK
#define NJOY_ACETK_BLOCK_FRAMEANDMULTIPLICITYBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/block/details/Base.hpp"
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
class FrameAndMultiplicityBlock : protected details::Base {

  /* fields */
  unsigned int ntr_;

  /* auxiliary functions */
  #include "ACEtk/block/FrameAndMultiplicityBlock/src/generateXSS.hpp"
  #include "ACEtk/block/FrameAndMultiplicityBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/FrameAndMultiplicityBlock/src/ctor.hpp"

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
   *  @brief Return the reference frame for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  ReferenceFrame referenceFrame( std::size_t index ) const {

    return this->XSS( index ) < 0 ? ReferenceFrame::CentreOfMass
                                  : ReferenceFrame::Laboratory;
  }

  /**
   *  @brief Return the reference frames
   */
  auto referenceFrames() const {

    return this->XSS( 1, this->NTR() )
             | ranges::cpp20::views::transform(
                 [] ( const auto& value ) -> ReferenceFrame
                    { return value < 0 ? ReferenceFrame::CentreOfMass
                                       : ReferenceFrame::Laboratory; } );
  }

  /**
   *  @brief Return the multiplicity value for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int multiplicity( std::size_t index ) const {

    return std::abs( this->XSS( index ) );
  }

  /**
   *  @brief Return the multiplicities
   */
  auto multiplicities() const {

    return this->XSS( 1, this->NTR() )
             | ranges::cpp20::views::transform(
                 [] ( const auto& value ) { return std::abs( value ); } );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using TYR = FrameAndMultiplicityBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
