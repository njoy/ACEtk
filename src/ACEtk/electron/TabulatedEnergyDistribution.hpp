#ifndef NJOY_ACETK_BLOCK_ELECTRONTABULATEDENERGYDISTRIBUTION
#define NJOY_ACETK_BLOCK_ELECTRONTABULATEDENERGYDISTRIBUTION

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated photon energy distribution from Bremsstrahlung for a single
 *         incident energy
 *
 *  The ElectronTabulatedEnergyDistribution class contains the cumulative
 *  density function (CDF) as a function of photon energy for the given incident
 *  energy. It is used in the BREME block.
 */
class ElectronTabulatedEnergyDistribution : protected details::ArrayData {

  /* fields */
  double energy_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/ElectronTabulatedEnergyDistribution/src/ctor.hpp"

  /**
   *  @brief Return the associated incident energy value
   */
  double energy() const { return this->energy_; }

  /**
   *  @brief Return the number of outgoing energy values
   */
  std::size_t L() const { return this->N(); }

  /**
   *  @brief Return the number of outgoing energy values
   */
  std::size_t LB() const { return this->L(); }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t numberOutgoingEnergies() const { return this->LB(); }

  /**
   *  @brief Return the outgoing energy values
   */
  auto outgoingEnergies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the cdf values
   */
  auto cdf() const { return this->darray( 2 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
