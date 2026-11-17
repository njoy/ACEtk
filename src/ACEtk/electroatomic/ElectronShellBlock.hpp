#ifndef NJOY_ACETK_ELECTROATOMIC_ELECTRONSHELLBLOCK
#define NJOY_ACETK_ELECTROATOMIC_ELECTRONSHELLBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

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
class ElectronShellBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  ElectronShellBlock() = default;

  ElectronShellBlock( const ElectronShellBlock& ) = default;
  ElectronShellBlock( ElectronShellBlock&& ) = default;

  ElectronShellBlock& operator=( const ElectronShellBlock& ) = default;
  ElectronShellBlock& operator=( ElectronShellBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] electrons        the number of electrons for each shell
   *  @param[in] energies         the binding energy for each shell
   *  @param[in] probabilities    the interaction probability for each shell
   */
  ElectronShellBlock( std::vector< double > electrons,
                      std::vector< double > energies,
                      std::vector< double > probabilities ) :
    ArrayData( "EPS",
               std::vector< std::vector< double > > {

                 std::move( electrons ),
                 std::move( energies ),
                 std::move( probabilities )
               } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the EPS block in the XSS array
   *  @param[in] end     the end iterator of the EPS block in the XSS array
   *  @param[in] nsh     the number of electron shells
   */
  ElectronShellBlock( Iterator begin, Iterator end, unsigned int nsh ) :
    ArrayData( "EPS", begin, end, nsh, 3 ) {}

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

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
