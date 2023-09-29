#ifndef NJOY_ACETK_ELECTRON_PRINCIPALCROSSSECTIONBLOCK
#define NJOY_ACETK_ELECTRON_PRINCIPALCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron ESZE block with the electron cross section data
 *
 *  This block is part of the eprdata formats.
 *
 *  The PrincipalCrossSectionBlock class contains 5 + NSSH arrays of the same
 *  length:
 *    - the energy points
 *    - the total cross section (sum of the following three arrays)
 *    - the elastic scattering cross section
 *    - the Bremsstrahlung cross section
 *    - the excitation cross section
 *    - the total electroionisation cross section (sum of the following NSSH arrays)
 *    - the electroionisation cross section for each subshell (NSSH arrays)
 *
 *  The size NE of each (the total number of electron energy points) is stored in
 *  NXS(8). The number of subshells NSSH is stored in NXS(7).
 */
class PrincipalCrossSectionBlock : protected block::details::ArrayData {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/electron/PrincipalCrossSectionBlock/src/verifyIndex.hpp"
  #include "ACEtk/electron/PrincipalCrossSectionBlock/src/generateArrays.hpp"

public:

  /* constructor */
  #include "ACEtk/electron/PrincipalCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NE() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the number of electron subshells
   */
  unsigned int NSSH() const { return this->M() - 6; }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronSubshells() const { return this->NSSH(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the total cross section values
   */
  auto total() const { return this->darray( 2 ); }

  /**
   *  @brief Return the elastic cross section values
   */
  auto elastic() const { return this->darray( 3 ); }

  /**
   *  @brief Return the Bremsstrahlung cross section values
   */
  auto bremsstrahlung() const { return this->darray( 4 ); }

  /**
   *  @brief Return the excitation cross section values
   */
  auto excitation() const { return this->darray( 5 ); }

  /**
   *  @brief Return the total electroionisation cross section values
   */
  auto totalElectroionisation() const { return this->darray( 6 ); }

  /**
   *  @brief Return the electroionisation cross section values for a specific
   *         shell
   *
   *  @param[in] index    the electron subshell index (one-based)
   */
  auto electroionisation( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( index );
    #endif
    return this->darray( 6 + index );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ESZE = PrincipalCrossSectionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
