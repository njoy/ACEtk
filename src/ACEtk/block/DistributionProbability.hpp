#ifndef NJOY_ACETK_BLOCK_LAWPROBABILITY
#define NJOY_ACETK_BLOCK_LAWPROBABILITY

// system includes

// other includes
#include "ACEtk/block/details/BaseTabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The probability for a distribution to occur
 */
class DistributionProbability : protected details::BaseTabulatedData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/DistributionProbability/src/ctor.hpp"

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return BaseTabulatedData::interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return BaseTabulatedData::NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return BaseTabulatedData::numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return BaseTabulatedData::NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return BaseTabulatedData::boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return BaseTabulatedData::INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return BaseTabulatedData::interpolants(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t NE() const { return BaseTabulatedData::N(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t numberEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return BaseTabulatedData::x(); }

  /**
   *  @brief Return the parameter values
   */
  auto probabilities() const { return BaseTabulatedData::y(); }

  using BaseTabulatedData::empty;
  using BaseTabulatedData::name;
  using BaseTabulatedData::length;
  using BaseTabulatedData::XSS;
  using BaseTabulatedData::begin;
  using BaseTabulatedData::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
