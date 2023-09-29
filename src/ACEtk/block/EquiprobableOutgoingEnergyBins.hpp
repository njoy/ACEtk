#ifndef NJOY_ACETK_BLOCK_EQUIPROBABLEOUTGOINGENERGYBINS
#define NJOY_ACETK_BLOCK_EQUIPROBABLEOUTGOINGENERGYBINS

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Equiprobable outgoing energy bin data for a single incident energy
 *
 *  The EquiprobableOutgoingEnergyBins class contains the outgoing energy values
 *  that make up the equiprobable bins and the associated incident energy. It is
 *  used in the EquiprobableOutgoingEnergyBinData (ACE LAW 1 for a given incident
 *  energy) in the DLW block. This format is only used in old ACE data.
 */
class EquiprobableOutgoingEnergyBins : protected details::Base {

  /* fields */
  double incident_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/EquiprobableOutgoingEnergyBins/src/ctor.hpp"

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->incident_; }

  /**
   *  @brief Return the number of equiprobable angular bins
   */
  int numberBins() const { return this->length() - 1; }

  /**
   *  @brief Return the energy values
   */
  auto energies() const {

    return this->XSS( 1, this->numberBins() + 1 );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
