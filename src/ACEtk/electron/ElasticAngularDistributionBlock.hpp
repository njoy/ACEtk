#ifndef NJOY_ACETK_ELECTRON_ELASTICANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_ELECTRON_ELASTICANGULARDISTRIBUTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ElectronBlockWithLocators.hpp"
#include "ACEtk/electron/TabulatedAngularDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron ELASI and ELAS block with the large angle elastic
 *         scattering angular distribution data
 *
 *  The ElasticAngularDistributionBlock class a list of electron energies
 *  for which angular distribution data is given.
 */
class ElasticAngularDistributionBlock :
    protected base::ElectronBlockWithLocators< ElasticAngularDistributionBlock,
                                               TabulatedAngularDistribution > {

  friend class base::ElectronBlockWithLocators< ElasticAngularDistributionBlock,
                                                TabulatedAngularDistribution >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electron/ElasticAngularDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available energies
   */
  unsigned int NA() const { return ElectronBlockWithLocators::N(); }

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
   *  @brief Return all angular distribution data
   */
  const std::vector< TabulatedAngularDistribution >& distributions() const {

    return ElectronBlockWithLocators::data();
  }

  /**
   *  @brief Return the angular distribution for an energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const TabulatedAngularDistribution&
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

using ELAS = ElasticAngularDistributionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
