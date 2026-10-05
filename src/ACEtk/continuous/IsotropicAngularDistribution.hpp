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

  IsotropicAngularDistribution() = default;

  IsotropicAngularDistribution( const IsotropicAngularDistribution& ) = default;
  IsotropicAngularDistribution( IsotropicAngularDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energy    the associated energy value
   */
  IsotropicAngularDistribution( double energy ) :
    energy_( energy ) {}

  IsotropicAngularDistribution& operator=( const IsotropicAngularDistribution& ) = default;
  IsotropicAngularDistribution& operator=( IsotropicAngularDistribution&& ) = default;

  /**
   *  @brief Return the associated energy value
   */
  double energy() const { return this->energy_; }
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
