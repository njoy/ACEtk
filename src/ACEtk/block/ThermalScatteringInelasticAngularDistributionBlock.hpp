#ifndef NJOY_ACETK_BLOCK_THERMALSCATTERINGINELASTCANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_THERMALSCATTERINGINELASTCANGULARDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/ThermalScatteringDiscreteCosines.hpp"
#include "ACEtk/block/ThermalScatteringDiscreteCosinesWithProbability.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The angular distribution block for inelastic thermal scattering
 *         using equiprobable discrete cosines or a skewed distribution of
 *         discrete cosines
 *
 *  The ThermalScatteringInelasticAngularDistributionBlock class contains
 *  the equiprobable set or skewed distribution of discrete cosines.
 */
class ThermalScatteringInelasticAngularDistributionBlock : protected details::Base {

public:

  /* type alias */
  using AngularDistributionData =
  std::variant< ThermalScatteringDiscreteCosines,
                ThermalScatteringDiscreteCosinesWithProbability >;

private:

  /* fields */
  unsigned int ifeng_;
  std::size_t nc_;
  std::optional< std::size_t > nieb_;
  std::size_t ne_;
  std::vector< std::vector< AngularDistributionData > > data_;

  /* auxiliary functions */
  #include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock/src/generateBlocks.hpp"
  #include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock/src/verifyIndices.hpp"
  #include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock/src/verifySize.hpp"
  #include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock/src/ctor.hpp"

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int IFENG() const { return this->ifeng_; }

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int secondaryEnergyMode() const { return this->IFENG(); }

  /**
   *  @brief Return the number of equiprobable discrete cosine values for each
   *         incident and outgoing energy pair
   */
  std::size_t NC() const { return this->nc_; }

  /**
   *  @brief Return the number of equiprobable discrete cosine values for each
   *         incident and outgoing energy pair
   */
  std::size_t numberDiscreteCosines() const { return this->NC(); }

  /**
   *  @brief Return the inelastic dimensioning parameter
   */
  std::size_t NIL() const { return this->NC() - 1; }

  /**
   *  @brief Return the inelastic dimensioning parameter
   */
  std::size_t inelasticDimensioningParameter() const { return this->NIL(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return this->ne_; }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the number of outgoing energy values (not used for ifeng = 2)
   */
  const std::optional< std::size_t >& NIEB() const { return this->nieb_; }

  /**
   *  @brief Return the number of outgoing energy values (not used for ifeng = 2)
   */
  const std::optional< std::size_t >& numberOutgoingEnergies() const {

    return this->NIEB();
  }

  /**
   *  @brief Return the discrete cosine data for an incident and outgoing energy
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] incident    the incident energy index (one-based)
   *  @param[in] outgoing    the outgoing energy index (one-based)
   */
  auto discreteCosineData( std::size_t incident, std::size_t outgoing ) const {

    #ifndef NDEBUG
    this->verifyIndices( incident, outgoing );
    #endif
    return this->data_[ incident - 1 ][ outgoing - 1 ];
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ITXE = ThermalScatteringInelasticAngularDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
