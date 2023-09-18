#ifndef NJOY_ACETK_BLOCK_ELECTRONTABULATEDANGULARDISTRIBUTION
#define NJOY_ACETK_BLOCK_ELECTRONTABULATEDANGULARDISTRIBUTION

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated angular distribution data for a single incident or outgoing
 *         energy
 *
 *  The TabulatedAngularDistribution class contains the probability density
 *  function (PDF) and cumulative density function (CDF) as a function of
 *  cosine for the given energy. It is used in the AND block.
 */
class ElectronTabulatedAngularDistribution : protected details::ArrayData {

  /* fields */
  double energy_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/ElectronTabulatedAngularDistribution/src/ctor.hpp"

  /**
   *  @brief Return the associated energy value
   */
  double energy() const { return this->energy_; }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t LA() const { return this->N(); }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t numberCosines() const { return this->LA(); }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const { return this->darray( 1 ); }

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
