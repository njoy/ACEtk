#ifndef NJOY_ACETK_BLOCK_MULTIEVAPORATIONSPECTRUM
#define NJOY_ACETK_BLOCK_MULTIEVAPORATIONSPECTRUM

// system includes
#include <variant>

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/details/MultiDistribution.hpp"
#include "ACEtk/block/EvaporationSpectrum.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The distribution is a combination of multiple EvaporationSpectrum
 *
 *  The MultiEvaporationSpectrum class contains a set of evaporation spectra and
 *  associated probabilities to represent the particle's distribution data.
 *  It is used in the DLW block (there is no ACE LAW associated to this
 *  distribution type, but internally in ACEtk we refer to it as ACE LAW 6669
 *  because it is evil).
 */
class MultiEvaporationSpectrum :
  protected details::MultiDistribution< MultiEvaporationSpectrum, EvaporationSpectrum > {

  friend class details::MultiDistribution< MultiEvaporationSpectrum,
                                           EvaporationSpectrum >;

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/MultiEvaporationSpectrum/src/readDistributionData.hpp"
  #include "ACEtk/block/MultiEvaporationSpectrum/src/retrieveLAW.hpp"
  #include "ACEtk/block/MultiEvaporationSpectrum/src/insertXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/MultiEvaporationSpectrum/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::MultiEvaporation;
  }

  using MultiDistribution::type;
  using MultiDistribution::numberDistributions;
  using MultiDistribution::probabilities;
  using MultiDistribution::probability;
  using MultiDistribution::distributions;
  using MultiDistribution::distribution;
  using MultiDistribution::empty;
  using MultiDistribution::name;
  using MultiDistribution::length;
  using MultiDistribution::XSS;
  using MultiDistribution::begin;
  using MultiDistribution::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
