#ifndef NJOY_ACETK_CONTINUOUS_TWOBODYTRANSFERDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_TWOBODYTRANSFERDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/TwoParameterDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The energy distribution uses two body transfer
 *
 *  It is used in the DLW block as ACE LAW 33.
 */
class TwoBodyTransferDistribution : protected base::TwoParameterDistribution {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  TwoBodyTransferDistribution() = default;

  TwoBodyTransferDistribution( const TwoBodyTransferDistribution& ) = default;
  TwoBodyTransferDistribution( TwoBodyTransferDistribution&& ) = default;

  TwoBodyTransferDistribution& operator=( const TwoBodyTransferDistribution& ) = default;
  TwoBodyTransferDistribution& operator=( TwoBodyTransferDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] emin    the minimum energy for the distribution
   *  @param[in] emax    the maximum energy for the distribution
   *  @param[in] c1      the value of C1
   *  @param[in] c2      the value of C2
   */
  TwoBodyTransferDistribution( double emin, double emax, double c1, double c2 ) :
    TwoParameterDistribution( "TwoBodyTransferDistribution", emin, emax, c1, c2 ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the block
   *  @param[in] end     the end iterator of the block
   *  @param[in] emin    the minimum energy for the distribution
   *  @param[in] emax    the maximum energy for the distribution
   */
  TwoBodyTransferDistribution( Iterator begin, Iterator end,
                               double emin, double emax ) :
    TwoParameterDistribution( "TwoBodyTransferDistribution", begin, end, emin, emax ) {}

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::TwoBodyTransfer;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::TwoBodyTransfer;
  }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return TwoParameterDistribution::minimumIncidentEnergy();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return TwoParameterDistribution::maximumIncidentEnergy();
  }

  /**
   *  @brief Return the value of C1
   */
  double C1() const { return TwoParameterDistribution::C1(); }

  /**
   *  @brief Return the value of C2
   */
  double C2() const { return TwoParameterDistribution::C2(); }

  using TwoParameterDistribution::empty;
  using TwoParameterDistribution::name;
  using TwoParameterDistribution::length;
  using TwoParameterDistribution::XSS;
  using TwoParameterDistribution::begin;
  using TwoParameterDistribution::end;
};

using ACELAW33 = TwoBodyTransferDistribution;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
