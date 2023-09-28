#ifndef NJOY_ACETK_ELECTRON_ELECTRONSHELLBLOCK
#define NJOY_ACETK_ELECTRON_ELECTRONSHELLBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron LNEPS, LBEPS and LPIPS block with the electron shell data
 *
 *  The ElectronShellBlock class contains 3 arrays of the same length:
 *    - the number of electrons for each shell
 *    - the binding energy for each shell
 *    - the interaction probability for each shell
 *
 *  The size of each (the total number of electron shells) is stored in NXS(5).
 */
class ElectronShellBlock : protected block::details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electron/ElectronShellBlock/src/ctor.hpp"

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int NSH() const { return this->N(); }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronShells() const { return this->NSH(); }

  /**
   *  @brief Return the number of electrons for each shell
   */
  auto LNEPS() const { return this->darray( 1 ); }

  /**
   *  @brief Return the number of electrons for each shell
   */
  auto numberElectrons() const { return this->LNEPS(); }

  /**
   *  @brief Return the binding energy for each shell
   */
  auto LBEPS() const { return this->darray( 2 ); }

  /**
   *  @brief Return the binding energy for each shell
   */
  auto bindingEnergies() const { return this->LBEPS(); }

  /**
   *  @brief Return the interaction probability for each shell
   */
  auto LPIPS() const { return this->darray( 3 ); }

  /**
   *  @brief Return the interaction probability for each shell
   */
  auto interactionProbabilities() const { return this->LPIPS(); }

  /**
   *  @brief Return the number of electrons on a specific shell
   *
   *  @param[in] index    the electron shell index (one-based)
   */
  unsigned int numberElectronsPerShell( std::size_t index ) const {

    return this->ivalue( 1, index );
  }

  /**
   *  @brief Return the binding energy for a specific shell
   *
   *  @param[in] index    the electron shell index (one-based)
   */
  double bindingEnergy( std::size_t index ) const {

    return this->dvalue( 2, index );
  }

  /**
   *  @brief Return the interaction probability for a specific shell
   *
   *  @param[in] index    the electron shell index (one-based)
   */
  auto interactionProbability( std::size_t index ) const {

    return this->dvalue( 3, index );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using EPS = ElectronShellBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
