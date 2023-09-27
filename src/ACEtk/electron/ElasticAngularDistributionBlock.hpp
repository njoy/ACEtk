#ifndef NJOY_ACETK_ELECTRON_ELASTICANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_ELECTRON_ELASTICANGULARDISTRIBUTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/BaseElectronBlockWithLocators.hpp"
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
    protected block::details::BaseElectronBlockWithLocators<
                  ElasticAngularDistributionBlock,
                  TabulatedAngularDistribution > {

  friend class block::details::BaseElectronBlockWithLocators<
                   ElasticAngularDistributionBlock,
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
  unsigned int NA() const { return BaseElectronBlockWithLocators::N(); }

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
   *  @brief Return all angular distribution data
   */
  const std::vector< TabulatedAngularDistribution >& distributions() const {

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
  const TabulatedAngularDistribution&
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

using ELAS = ElasticAngularDistributionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
