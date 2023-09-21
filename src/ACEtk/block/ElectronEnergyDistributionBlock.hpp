#ifndef NJOY_ACETK_BLOCK_ELECTRONENERGYDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_ELECTRONENERGYDISTRIBUTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/BaseElectronBlockWithLocators.hpp"
#include "ACEtk/block/ElectronTabulatedEnergyDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The energy distribution block for photons from Bremsstrahlung or
 *         knock-on electrons for a specific subshell
 *
 *  The ElectronEnergyDistributionBlock class contains a list of electron
 *  energies for which energy distribution data is given (for either photons in
 *  the BREMI/BREME block or electrons in the EION blocks).
 */
class ElectronEnergyDistributionBlock :
    protected details::BaseElectronBlockWithLocators<
                  ElectronEnergyDistributionBlock,
                  ElectronTabulatedEnergyDistribution > {

  friend class details::BaseElectronBlockWithLocators<
                   ElectronEnergyDistributionBlock,
                   ElectronTabulatedEnergyDistribution >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/ElectronEnergyDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available energies
   */
  unsigned int NB() const { return BaseElectronBlockWithLocators::N(); }

  /**
   *  @brief Return the number of available energies
   */
  unsigned int numberEnergyPoints() const {

    return BaseElectronBlockWithLocators::numberDataBlocks();
  }

  /**
   *  @brief Return the relative distribution locator for an energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LLOC( std::size_t index ) const {

    return BaseElectronBlockWithLocators::LLOC( index );
  }

  /**
   *  @brief Return the relative distribution locator for an energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t distributionLocator( std::size_t index ) const {

    return BaseElectronBlockWithLocators::locator( index );
  }

  /**
   *  @brief Return the energy values
   */
  auto energies() const {

    return BaseElectronBlockWithLocators::energies();
  }

  /**
   *  @brief Return all energy distribution data
   */
  const std::vector< ElectronTabulatedEnergyDistribution >& distributions() const {

    return BaseElectronBlockWithLocators::data();
  }

  /**
   *  @brief Return the energy distribution for an energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const ElectronTabulatedEnergyDistribution&
  distribution( std::size_t index ) const {

    return BaseElectronBlockWithLocators::data( index );
  }

  using BaseElectronBlockWithLocators::empty;
  using BaseElectronBlockWithLocators::name;
  using BaseElectronBlockWithLocators::length;
  using BaseElectronBlockWithLocators::XSS;
  using BaseElectronBlockWithLocators::begin;
  using BaseElectronBlockWithLocators::end;
};

using BREME = ElectronEnergyDistributionBlock;
using EION = ElectronEnergyDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
