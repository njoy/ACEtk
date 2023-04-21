#ifndef NJOY_ACETK_BLOCK_DELAYEDNEUTRONPRECURSORDATA
#define NJOY_ACETK_BLOCK_DELAYEDNEUTRONPRECURSORDATA

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/details/BaseTabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Delayed neutron precursor group data
 *
 *  The DelayedNeutronPrecursorData class contains the prrcursor group's decay
 *  constant and the associated probability as a function of incident energy.
 */
class DelayedNeutronPrecursorData : protected details::Base {

  /* fields */
  details::BaseTabulatedData data_;

  /* auxiliary functions */
  #include "ACEtk/block/DelayedNeutronPrecursorData/src/generateXSS.hpp"
  #include "ACEtk/block/DelayedNeutronPrecursorData/src/generateBlocks.hpp"

public:

  /* constructor */
  #include "ACEtk/block/DelayedNeutronPrecursorData/src/ctor.hpp"

  /**
   *  @brief Return the decay constant
   */
  double DEC() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the decay constant
   */
  double decayConstant() const { return this->DEC(); }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const { return this->data_.interpolationData(); }

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
   *  @brief Return the number of values
   */
  std::size_t NE() const { return this->data_.N(); }

  /**
   *  @brief Return the number of values
   */
  std::size_t numberValues() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return this->data_.x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the probabilities
   */
  auto P() const { return this->data_.y(); }

  /**
   *  @brief Return the probabilities
   */
  auto probabilities() const { return this->P(); }

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
