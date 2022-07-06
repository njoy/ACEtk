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
 *
 *  The ThermalScatteringInelasticAngularDistributionBlock class contains
 *  the equiprobable set or a skewed distribution of discrete cosines, or a
 *  tabulated probability distribution.
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
  std::size_t locb_;
  std::vector< std::vector< AngularDistributionData > > data_;

  /* auxiliary functions */
  #include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock/src/generateBlocks.hpp"
  #include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock/src/verifyIndices.hpp"
  #include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock/src/verifySize.hpp"
  #include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock/src/generateXSS.hpp"

  /**
   *  @brief Return the distribution locator for an incident energy index
   *
   *  This locator is the value as stored in the XSS array.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LOCC( std::size_t index ) const {

    return this->IXSS( index );
  }

  /**
   *  @brief Return the distribution locator for an incident energy index
   *
   *  This locator is the value as stored in the XSS array.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int distributionLocator( std::size_t index ) const {

    return this->LOCC( index );
  }

  /**
   *  @brief Return the relative distribution locator for a value index
   *
   *  This is the locator relative to the beginning of the current distribution
   *  block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t relativeDistributionLocator( std::size_t index ) const {

    const int locator = this->LOCC( index );
    return locator - this->locb_ + 1;
  }

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
   *  @brief Return the number of secondary energies for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t NIEB( std::size_t index ) const {

    if ( this->nieb_ ) {

      return this->nieb_.value();
    }
    else {

      #ifndef NDEBUG
      this->verifyIndex( index );
      #endif
      return this->IXSS( this->NE() + index );
    }
  }

  /**
   *  @brief Return the number of secondary energies for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t numberOutgoingEnergies( std::size_t index ) const {

    return this->NIEB( index );
  }

  /**
   *  @brief Return all angular distribution data
   */
  const std::vector< std::vector< AngularDistributionData > >& data() const {

    return this->data_;
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
