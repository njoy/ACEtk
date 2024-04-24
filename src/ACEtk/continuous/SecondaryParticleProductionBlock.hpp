#ifndef NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEPRODUCTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEPRODUCTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Total production cross section and heating numbers for a secondary
 *         particle
 *
 *  The SecondaryParticleProductionBlock class contains the index of the
 *  energy point corresponding to the first cross section value, the number of
 *  cross section values and the actual production cross section values and
 *  heating numbers.
 */
class SecondaryParticleProductionBlock : protected base::Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/continuous/SecondaryParticleProductionBlock/src/generateXSS.hpp"
  #include "ACEtk/continuous/SecondaryParticleProductionBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/SecondaryParticleProductionBlock/src/ctor.hpp"

  /**
   *  @brief Return the energy index
   */
  std::size_t energyIndex() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of cross section values
   */
  std::size_t numberValues() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the total production cross section values
   */
  auto totalProduction() const {

    return this->XSS( 3, this->numberValues() );
  }

  /**
   *  @brief Return the heating numbers
   */
  auto heating() const {

    return this->XSS( 3 + this->numberValues(), this->numberValues() );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using HPD = SecondaryParticleProductionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
