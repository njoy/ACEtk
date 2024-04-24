#ifndef NJOY_ACETK_CONTINUOUS_MULTIPLICITYREACTIONNUMBERBLOCK
#define NJOY_ACETK_CONTINUOUS_MULTIPLICITYREACTIONNUMBERBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy YP block with the reaction MT numbers required
 *         for production cross section calculation
 *
 *  The MultiplicityReactionNumberBlock class contains the reaction MT numbers
 *  that are needed in production cross section calculations using multiplicity
 *  values.
 */
class MultiplicityReactionNumberBlock : protected base::Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/continuous/MultiplicityReactionNumberBlock/src/generateXSS.hpp"
  #include "ACEtk/continuous/MultiplicityReactionNumberBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/MultiplicityReactionNumberBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of multiplicity based production reactions
   */
  unsigned int NYP() const {

    return this->empty() ? 0 : static_cast< unsigned int >( this->IXSS(1) );
  }

  /**
   *  @brief Return the number of multiplicity based production reactions
   */
  unsigned int numberReactions() const { return this->NYP(); }

  /**
   *  @brief Return the reaction number for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int MT( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyReactionIndex( index, 1, this->NYP() );
    #endif
    return static_cast< unsigned int >( this->IXSS( index + 1 ) );
  }

  /**
   *  @brief Return the reaction number for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int reactionNumber( std::size_t index ) const {

    return this->MT( index );
  }

  /**
   *  @brief Return the reaction numbers
   */
  auto MTs() const { return this->XSS( 2, this->NYP() ); }

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

    return std::find_if(
               this->begin() + 1, this->end(),
               [reaction] ( auto&& value ) {

                 return static_cast< unsigned int >( std::round( value ) )
                        == reaction;
               } ) != this->end();
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

    auto iter = std::find_if(
                    this->begin() + 1, this->end(),
                    [reaction] ( auto&& value ) {

                      return static_cast< unsigned int >( std::round( value ) )
                             == reaction;
                    } );
    if ( iter != this->end() ) {

      return std::distance( this->begin() + 1, iter ) + 1;
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

using YP = MultiplicityReactionNumberBlock;
using YH = MultiplicityReactionNumberBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
