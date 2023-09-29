#ifndef NJOY_ACETK_ELECTRON_TABULATEDANGULARDISTRIBUTION
#define NJOY_ACETK_ELECTRON_TABULATEDANGULARDISTRIBUTION

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief Tabulated electron angular distribution data for a single incident
 *         energy
 *
 *  The TabulatedAngularDistribution class contains the cumulative
 *  density function (CDF) as a function of cosine for the given incident
 *  energy. It is used in the ELAS block.
 */
class TabulatedAngularDistribution : protected block::details::ArrayData {

  /* fields */
  double energy_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electron/TabulatedAngularDistribution/src/ctor.hpp"

  /**
   *  @brief Return the associated incident energy value
   */
  double energy() const { return this->energy_; }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t L() const { return this->N(); }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t LA() const { return this->L(); }

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

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
