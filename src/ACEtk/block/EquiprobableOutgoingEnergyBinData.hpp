#ifndef NJOY_ACETK_BLOCK_EQUIPROBABLEOUTGOINGENERGYBINDATA
#define NJOY_ACETK_BLOCK_EQUIPROBABLEOUTGOINGENERGYBINDATA

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/EquiprobableOutgoingEnergyBins.hpp"
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/details/ColumnData.hpp"
#include "ACEtk/block/InterpolationData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Equiprobable outgoing energy bin data
 *
 *  The EquiprobableOutgoingEnergyBinData class contains the equiprobable bins
 *  for a set of incident energy values. It is used in the AND block. This
 *  format is only used in old ACE data. It is used in the DLW block as ACE LAW 1.
 */
class EquiprobableOutgoingEnergyBinData : protected details::Base {

  /* fields */
  InterpolationData interpolation_;
  details::ColumnData energies_;
  std::vector< EquiprobableOutgoingEnergyBins > bins_;

  /* auxiliary functions */
  #include "ACEtk/block/EquiprobableOutgoingEnergyBinData/src/verifySize.hpp"
  #include "ACEtk/block/EquiprobableOutgoingEnergyBinData/src/verifyIncidentEnergyIndex.hpp"
  #include "ACEtk/block/EquiprobableOutgoingEnergyBinData/src/generateBlocks.hpp"
  #include "ACEtk/block/EquiprobableOutgoingEnergyBinData/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/EquiprobableOutgoingEnergyBinData/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::Equiprobable;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::Equiprobable;
  }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const { return this->interpolation_; }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return this->interpolationData().NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const { return this->NB(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return this->interpolationData().NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return this->interpolationData().INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return this->energies_.N(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->energies_.column( 1 ); }

  /**
   *  @brief Return the incident energy for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double incidentEnergy( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->energies_.value( 1, index );
  }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return this->incidentEnergy( 1 );
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return this->incidentEnergy( this->NE() );
  }

  /**
   *  @brief Return the number of outgoing energy values for each incident energy
   */
  std::size_t NET() const {

    std::size_t nr = this->NB();
    std::size_t ne = this->NE();
    return static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 + ne + 1 ) );
  }

  /**
   *  @brief Return the number of equiprobable outgoing energy bins
   */
  std::size_t numberBins() const { return this->NET() - 1; }

  /**
   *  @brief Return the distributions
   */
  const std::vector< EquiprobableOutgoingEnergyBins >& distributions() const {

    return this->bins_;
  }

  /**
   *  @brief Return the distribution for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const EquiprobableOutgoingEnergyBins& distribution( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->bins_[ index - 1 ];
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ACELAW1 = EquiprobableOutgoingEnergyBinData;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
