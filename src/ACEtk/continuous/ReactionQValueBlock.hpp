#ifndef NJOY_ACETK_CONTINUOUS_REACTIONQVALUEBLOCK
#define NJOY_ACETK_CONTINUOUS_REACTIONQVALUEBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

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
class ReactionQValueBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  ReactionQValueBlock() = default;

  ReactionQValueBlock( const ReactionQValueBlock& ) = default;
  ReactionQValueBlock( ReactionQValueBlock&& ) = default;

  ReactionQValueBlock& operator=( const ReactionQValueBlock& ) = default;
  ReactionQValueBlock& operator=( ReactionQValueBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] qvalues    the Q values
   */
  ReactionQValueBlock( std::vector< double > qvalues ) :
    ArrayData( "LQR",
               std::vector< std::vector< double > >{ std::move( qvalues ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the LQR block in the XSS array
   *  @param[in] end     the end iterator of the LQR block in the XSS array
   *  @param[in] ntr     the number of reactions (excluding elastic)
   */
  ReactionQValueBlock( Iterator begin, Iterator end, unsigned int ntr ) :
    ArrayData( "LQR", begin, end, ntr, 1 ) {}

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

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
