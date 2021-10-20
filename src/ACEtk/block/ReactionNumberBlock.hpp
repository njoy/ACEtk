#ifndef NJOY_ACETK_BLOCK_REACTIONNUMBERBLOCK
#define NJOY_ACETK_BLOCK_REACTIONNUMBERBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/block/details/Base.hpp"

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
class ReactionNumberBlock : protected details::Base {

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
   *  @brief Return the reaction number for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  auto MT( std::size_t index ) const { return this->XSS( index ); }

  /**
   *  @brief Return the reaction number for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  auto reactionNumber( std::size_t index ) const { return this->MT( index ); }

  /**
   *  @brief Return the reaction numbers
   */
  auto MTs() const { return this->XSS( 1, this->NTR() ); }

  /**
   *  @brief Return the reaction numbers
   */
  auto reactionNumbers() const { return this->MTs(); }

  /**
   *  @brief Return whether or not the reaction number is present
   *
   *  @param[in] reaction    the reaction number
   */
  bool hasMT( unsigned int reaction ) const {

    return std::find( this->begin(), this->end(), reaction ) != this->end();
  }

  /**
   *  @brief Return whether or not the reaction number is present
   *
   *  @param[in] reaction    the reaction number
   */
  bool hasReactionNumber( unsigned int reaction ) const {

    return this->hasMT( reaction );
  }

  /**
   *  @brief Return the index (one-based) of the reaction number
   *
   *  @param[in] reaction    the reaction number
   */
  std::size_t index( unsigned int reaction ) const {

    auto iter = std::find( this->begin(), this->end(), reaction );
    if ( iter != this->end() ) {

      return std::distance( this->begin(), iter ) + 1;
    }
    else {

      Log::error( "The requested reaction number MT{} is not present", reaction );
      throw std::exception();
    }
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using MTR = ReactionNumberBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
