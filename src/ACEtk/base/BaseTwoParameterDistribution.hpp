#ifndef NJOY_ACETK_BASE_BASETWOPARAMETERDISTRIBUTION
#define NJOY_ACETK_BASE_BASETWOPARAMETERDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief Base class for a distribution using two parameters
 */
class BaseTwoParameterDistribution : protected Base {

  /* fields */
  double emin_;
  double emax_;

  /* auxiliary functions */
  #include "ACEtk/base/BaseTwoParameterDistribution/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/base/BaseTwoParameterDistribution/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::LevelScattering;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::LevelScattering;
  }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const { return this->emin_; }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const { return this->emax_; }

  /**
   *  @brief Return the value of C1
   */
  double C1() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the value of C2
   */
  double C2() const { return this->XSS( 2 ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
