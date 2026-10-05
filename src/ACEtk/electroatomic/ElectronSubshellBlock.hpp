#ifndef NJOY_ACETK_ELECTROATOMIC_ELECTRONSUBSHELLBLOCK
#define NJOY_ACETK_ELECTROATOMIC_ELECTRONSUBSHELLBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

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

  ElectronSubshellBlock() = default;

  ElectronSubshellBlock( const ElectronSubshellBlock& ) = default;
  ElectronSubshellBlock( ElectronSubshellBlock&& ) = default;

  ElectronSubshellBlock& operator=( const ElectronSubshellBlock& ) = default;
  ElectronSubshellBlock& operator=( ElectronSubshellBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] designators      the ENDF designator of each subshell
   *  @param[in] electrons        the electron population for each subshell
   *  @param[in] energies         the vacancy cumulative probability for each subshell
   *  @param[in] probabilities    the number of possible transitions to fill a vacancy
   *                              for each subshell
   */
  ElectronSubshellBlock( std::vector< unsigned int > designators,
                         std::vector< double > electrons,
                         std::vector< double > energies,
                         std::vector< double > probabilities,
                         std::vector< unsigned int > transitions ) :
    ArrayData( "SUBSH",
               std::vector< std::vector< double > > {

                 [] ( auto&& vector ) -> std::vector< double >
                    { return { vector.begin(), vector.end() }; }( designators ),
                 std::move( electrons ),
                 std::move( energies ),
                 std::move( probabilities ),
                 [] ( auto&& vector ) -> std::vector< double >
                    { return { vector.begin(), vector.end() }; }( transitions )
               } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the SUBSH block in the XSS array
   *  @param[in] end     the end iterator of the SUBSH block in the XSS array
   *  @param[in] nsh     the number of electron shells
   */
  ElectronSubshellBlock( Iterator begin, Iterator end, unsigned int nssh ) :
    ArrayData( "SUBSH", begin, end, nssh, 5 ) {}

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

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
