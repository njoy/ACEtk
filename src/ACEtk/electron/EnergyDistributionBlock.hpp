#ifndef NJOY_ACETK_ELECTRON_ENERGYDISTRIBUTIONBLOCK
#define NJOY_ACETK_ELECTRON_ENERGYDISTRIBUTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ElectronBlockWithLocators.hpp"
#include "ACEtk/electron/TabulatedEnergyDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The energy distribution block for photons from Bremsstrahlung or
 *         knock-on electrons for a specific subshell
 *
 *  The EnergyDistributionBlock class contains a list of electron energies for
 *  which energy distribution data is given (for either photons in the
 *  BREMI/BREME block or electrons in the EION blocks).
 */
class EnergyDistributionBlock :
    protected base::ElectronBlockWithLocators< EnergyDistributionBlock,
                                               TabulatedEnergyDistribution > {

  friend class base::ElectronBlockWithLocators< EnergyDistributionBlock,
                                                TabulatedEnergyDistribution >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electron/EnergyDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available energies
   */
  unsigned int NB() const { return ElectronBlockWithLocators::N(); }

  /**
   *  @brief Return the number of available energies
   */
  unsigned int numberEnergyPoints() const {

    return ElectronBlockWithLocators::numberDataBlocks();
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

    return ElectronBlockWithLocators::LLOC( index );
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

    return ElectronBlockWithLocators::locator( index );
  }

  /**
   *  @brief Return the energy values
   */
  auto energies() const {

    return ElectronBlockWithLocators::energies();
  }

  /**
   *  @brief Return all energy distribution data
   */
  const std::vector< TabulatedEnergyDistribution >& distributions() const {

    return ElectronBlockWithLocators::data();
  }

  /**
   *  @brief Return the energy distribution for an energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const TabulatedEnergyDistribution&
  distribution( std::size_t index ) const {

    return ElectronBlockWithLocators::data( index );
  }

  using ElectronBlockWithLocators::empty;
  using ElectronBlockWithLocators::name;
  using ElectronBlockWithLocators::length;
  using ElectronBlockWithLocators::XSS;
  using ElectronBlockWithLocators::begin;
  using ElectronBlockWithLocators::end;
};

using BREME = EnergyDistributionBlock;
using EION = EnergyDistributionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
