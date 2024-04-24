#ifndef NJOY_ACETK_ELECTRON_ELECTRONSUBSHELLBLOCK
#define NJOY_ACETK_ELECTRON_ELECTRONSUBSHELLBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron SUBSH block with the electron subshell data
 *
 *  This block is part of the eprdata formats.
 *
 *  The ElectronSubshellBlock class contains 5 arrays of the same length:
 *    - the ENDF designator of each subshell
 *    - the electron population for each subshell
 *    - the binding energy for each subshell
 *    - the vacancy cumulative probability for each subshell
 *    - the number of possible transitions to fill a vacancy for each subshell
 *
 *  The size of each (the total number of electron shells) is stored in NXS(7).
 */
class ElectronSubshellBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electron/ElectronSubshellBlock/src/ctor.hpp"

  /**
   *  @brief Return the number of electron subshells
   */
  unsigned int NSSH() const { return this->N(); }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronSubshells() const { return this->NSSH(); }

  /**
   *  @brief Return the ENDF designator for each subshell
   */
  auto ID() const { return this->iarray( 1 ); }

  /**
   *  @brief Return the ENDF designator for each subshell
   */
  auto designators() const { return this->ID(); }

  /**
   *  @brief Return the electron population for each subshell
   */
  auto EP() const { return this->darray( 2 ); }

  /**
   *  @brief Return the electron population for each subshell
   */
  auto populations() const { return this->EP(); }

  /**
   *  @brief Return the binding energies for each subshell
   */
  auto BE() const { return this->darray( 3 ); }

  /**
   *  @brief Return the binding energies for each subshell
   */
  auto bindingEnergies() const { return this->BE(); }

  /**
   *  @brief Return the vacancy cumulative probabilities for each subshell
   */
  auto CV() const { return this->darray( 4 ); }

  /**
   *  @brief Return the vacancy cumulative probabilities for each subshell
   */
  auto vacancyProbabilities() const { return this->CV(); }

  /**
   *  @brief Return the number of transitions to fill a vacancy for each subshell
   */
  auto NT() const { return this->iarray( 5 ); }

  /**
   *  @brief Return the number of transitions to fill a vacancy for each subshell
   */
  auto numberTransitions() const { return this->NT(); }

  /**
   *  @brief Return the ENDF designator for a specific shell
   *
   *  @param[in] index    the electron subshell index (one-based)
   */
  unsigned int designator( std::size_t index ) const {

    return this->ivalue( 1, index );
  }

  /**
   *  @brief Return the electron population for a specific shell
   *
   *  @param[in] index    the electron subshell index (one-based)
   */
  double population( std::size_t index ) const {

    return this->dvalue( 2, index );
  }

  /**
   *  @brief Return the binding energy for a specific shell
   *
   *  @param[in] index    the electron subshell index (one-based)
   */
  double bindingEnergy( std::size_t index ) const {

    return this->dvalue( 3, index );
  }

  /**
   *  @brief Return the vacancy probability for a specific shell
   *
   *  @param[in] index    the electron subshell index (one-based)
   */
  double vacancyProbability( std::size_t index ) const {

    return this->dvalue( 4, index );
  }

  /**
   *  @brief Return the number of transitions to fill a vacancy for a specific shell
   *
   *  @param[in] index    the electron subshell index (one-based)
   */
  unsigned int numberTransitions( std::size_t index ) const {

    return this->ivalue( 5, index );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using SUBSH = ElectronSubshellBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
