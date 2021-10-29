#ifndef NJOY_ACETK_BLOCK_ISOTROPICANGULARDISTRIBUTION
#define NJOY_ACETK_BLOCK_ISOTROPICANGULARDISTRIBUTION

// system includes

// other includes

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Isotropic angular distribution from the AND block for a single
 *         reaction and incident energy
 *
 *  The IsotropicAngularDistribution class contains contains no data other than
 *  the incident energy. It is a convenience interface object.
 */
class IsotropicAngularDistribution {

  /* fields */
  double incident_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/IsotropicAngularDistribution/src/ctor.hpp"

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->incident_; }
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
