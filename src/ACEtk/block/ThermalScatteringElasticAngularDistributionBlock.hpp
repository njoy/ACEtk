#ifndef NJOY_ACETK_BLOCK_THERMALSCATTERINGELASTCANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_THERMALSCATTERINGELASTCANGULARDISTRIBUTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The angular distribution block for elastic thermal scattering
 *
 *  The ThermalScatteringElasticAngularDistributionBlock class contains the
 *  a set of equally probable discrete cosine values for each incident energy
 *  value (the associated incident energy values are stored in the
 *  associated elastic thermal scattering cross section block).
 */
class ThermalScatteringElasticAngularDistributionBlock :
  protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/ThermalScatteringElasticAngularDistributionBlock/src/ctor.hpp"

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return this->M(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the number of equiprobable discrete cosine values for each
   *         incident energy value
   */
  std::size_t NC() const { return this->N(); }

  /**
   *  @brief Return the number of equiprobable discrete cosine values for each
   *         incident energy value
   */
  std::size_t numberDiscreteCosines() const { return this->NC(); }

  /**
   *  @brief Return the elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  std::size_t NCL() const { return this->NC() - 1; }

  /**
   *  @brief Return the elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  std::size_t elasticDimensioningParameter() const { return this->NCL(); }

  /**
   *  @brief Return the cosine values for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  auto cosines( std::size_t index ) const { return this->array( index ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ITCA = ThermalScatteringElasticAngularDistributionBlock;
using ITCAI = ThermalScatteringElasticAngularDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
