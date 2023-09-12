#ifndef NJOY_ACETK_BLOCK_PHOTOATOMICSUBSHELLTRANSITIONDATA
#define NJOY_ACETK_BLOCK_PHOTOATOMICSUBSHELLTRANSITIONDATA

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic transition data for a given subshell
 *
 *  This block is part of the eprdata formats.
 *
 *  The PhotoatomicSubshellTransitionData class contains the transition data
 *  to fill vacancies in the given subshell. Each transition has the following
 *  information associated to it:
 *    - the primary subshell designator (the designator of the subshell from
 *      where the electron is "moving" from)
 *    - the secondary subshell designator (the designator of the subshell from
 *      which the emitted electron is ejected or 0 for a radiative transition
 *      that only emits a photon)
 *    - the energy of the emitted photon or electron
 *    - the cumulative probability of the transition
 *
 *  The size NT of each (the total number of transitions) is stored in the SUBSH
 *  block. This data block may be empty (NT = 0).
 */
class PhotoatomicSubshellTransitionData : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/PhotoatomicSubshellTransitionData/src/generateArrays.hpp"

public:

  /* constructor */
  #include "ACEtk/block/PhotoatomicSubshellTransitionData/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NT() const { return this->M(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberTransitions() const { return this->NT(); }

  /**
   *  @brief Return the transition data for a given transition
   *
   *  @param[in] index      the transition index (one-based)
   */
  auto transition( std::size_t index ) const {

    return this->darray( index );
  }

  /**
   *  @brief Return the primary designator
   *
   *  @param[in] index      the transition index (one-based)
   */
  unsigned int primaryDesignator( std::size_t index ) const {

    return this->ivalue( index, 1 );
  }

  /**
   *  @brief Return the secondary designator
   *
   *  @param[in] index      the transition index (one-based)
   */
  unsigned int secondaryDesignator( std::size_t index ) const {

    return this->ivalue( index, 2 );
  }

  /**
   *  @brief Return the energy of the emitted photon or electron for a given
   *         transition
   *
   *  @param[in] index      the transition index (one-based)
   */
  double energy( std::size_t index ) const {

    return this->dvalue( index, 3 );
  }

  /**
   *  @brief Return the cumulative probability for a given transition
   *
   *  @param[in] index      the transition index (one-based)
   */
  double probability( std::size_t index ) const {

    return this->dvalue( index, 4 );
  }

  /**
   *  @brief Return whether or not the transition is a radiative transition
   *
   *  @param[in] index      the transition index (one-based)
   */
  bool isRadiativeTransition( std::size_t index ) const {

    return 0 == this->secondaryDesignator( index );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using TRAN = PhotoatomicSubshellTransitionData;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
