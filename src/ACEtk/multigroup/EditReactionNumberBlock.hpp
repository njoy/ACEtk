#ifndef NJOY_ACETK_MULTIGROUP_EDITREACTIONNUMBERBLOCK
#define NJOY_ACETK_MULTIGROUP_EDITREACTIONNUMBERBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup MTED block with the edit reaction numbers
 *
 *  The EditReactionNumberBlock class contains 1 array 
 *    - the edit reaction MT numbers
 *
 *  The size the array (the number of edit reactions) is stored in NXS(4).
 */
class EditReactionNumberBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

  #include "ACEtk/multigroup/EditReactionNumberBlock/src/iterator.hpp"

public:

  /* constructor */
  #include "ACEtk/multigroup/EditReactionNumberBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of edit reactions
   */
  unsigned int NEDIT() const { return this->N(); }

  /**
   *  @brief Return the number of edit reactions
   */
  unsigned int numberEditReactions() const { return this->NEDIT(); }

  /**
   *  @brief Return the reaction number for an index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int MT( std::size_t index ) const {

    return static_cast< unsigned int >( this->ivalue( 1, index ) );
  }

  /**
   *  @brief Return the reaction number for an index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int editReactionNumber( std::size_t index ) const {

    return this->MT( index );
  }

  /**
   *  @brief Return the edit reaction MT numbers
   */
  auto MTs() const { return this->darray( 1 ); }

  /**
   *  @brief Return the edit reaction MT numbers
   */
  auto editReactionNumbers() const { return this->MTs(); }

  /** 
  * @brief Return whether or not a reaction MT is present in the edit reactions
  *
  * @param[in] mt      the mt number
  */
  bool hasMT( unsigned int mt ) const {

    auto iter = this->iterator( mt );
    return iter != this->end();

  }

  /** 
  * @brief Return whether or not a reaction MT is present in the edit reactions
  *
  * @param[in] mt      the mt number
  */
  bool hasEditReactionNumber( unsigned int mt ) const {

    return this->hasMT( mt );

  }

  /**
   *  @brief Return the index (one-based) of the edit reaction number, if present
   *
   *  @param[in] mt    the reaction number
   */
  std::size_t index( unsigned int mt ) const { 

    auto iter = this->iterator( mt );
    if ( iter != this->end() ) {

      return std::distance( this->begin(), iter ) + 1; 
    }
    else {

      Log::error( "MT{} is not in the edit reaction numbers", mt );
      throw std::exception();
    }
  }



  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using MTED = EditReactionNumberBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
