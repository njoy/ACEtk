#ifndef NJOY_ACETK_CONTINUOUS_ISOTROPICANGULARDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_ISOTROPICANGULARDISTRIBUTION

// system includes

// other includes

namespace njoy {
namespace ACEtk {
namespace continuous {

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
  #include "ACEtk/continuous/IsotropicAngularDistribution/src/ctor.hpp"

  /**
   *  @brief Return the associated energy value
   */
  double energy() const { return this->energy_; }
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
