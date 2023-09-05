#ifndef NJOY_ACETK_BLOCK_ISOTROPICANGULARDISTRIBUTION
#define NJOY_ACETK_BLOCK_ISOTROPICANGULARDISTRIBUTION

// system includes

// other includes

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Isotropic angular distribution
 *
 *  The IsotropicAngularDistribution class contains contains no data other than
 *  the incident energy. It is a convenience interface object used in the AND block.
 */
class IsotropicAngularDistribution {

  /* fields */
  double energy_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/IsotropicAngularDistribution/src/ctor.hpp"

  /**
   *  @brief Return the associated energy value
   */
  double energy() const { return this->energy_; }
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
