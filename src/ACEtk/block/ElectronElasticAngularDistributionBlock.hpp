#ifndef NJOY_ACETK_BLOCK_ELECTRONANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_ELECTRONANGULARDISTRIBUTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/BaseElectronBlockWithLocators.hpp"
#include "ACEtk/block/ElectronTabulatedAngularDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic and electron ELASI and ELAS block with the
 *         elastic scattering angular distribution data
 *
 *  The ElectronElasticAngularDistributionBlock class a list of electron energies
 *  for which angular distribution data is given.
 */
class ElectronElasticAngularDistributionBlock :
    protected details::BaseElectronBlockWithLocators<
                  ElectronElasticAngularDistributionBlock,
                  ElectronTabulatedAngularDistribution > {

  friend class details::BaseElectronBlockWithLocators<
                   ElectronElasticAngularDistributionBlock,
                   ElectronTabulatedAngularDistribution >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/ElectronElasticAngularDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available energies
   */
  unsigned int NA() const { return BaseElectronBlockWithLocators::N(); }

  /**
   *  @brief Return the number of available energies
   */
  unsigned int numberEnergyPoints() const {

    return BaseElectronBlockWithLocators::numberDataBlocks();
  }

  /**
   *  @brief Return the relative angular distribution locator for an energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LAND( std::size_t index ) const {

    return BaseElectronBlockWithLocators::LLOC( index );
  }

  /**
   *  @brief Return the relative angular distribution locator for an energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t angularDistributionLocator( std::size_t index ) const {

    return BaseElectronBlockWithLocators::locator( index );
  }

  /**
   *  @brief Return the energy values
   */
  auto energies() const {

    return BaseElectronBlockWithLocators::energies();
  }

  /**
   *  @brief Return all angular distribution data
   */
  const std::vector< ElectronTabulatedAngularDistribution >& data() const {

    return BaseElectronBlockWithLocators::data();
  }

  /**
   *  @brief Return the angular distribution for an energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const ElectronTabulatedAngularDistribution&
  angularDistribution( std::size_t index ) const {

    return BaseElectronBlockWithLocators::data( index );
  }

  using BaseElectronBlockWithLocators::empty;
  using BaseElectronBlockWithLocators::name;
  using BaseElectronBlockWithLocators::length;
  using BaseElectronBlockWithLocators::XSS;
  using BaseElectronBlockWithLocators::begin;
  using BaseElectronBlockWithLocators::end;
};

using ELAS = ElectronElasticAngularDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
