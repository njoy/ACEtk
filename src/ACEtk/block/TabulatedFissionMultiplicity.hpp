#ifndef NJOY_ACETK_BLOCK_TABULATEDFISSIONMULTIPLICITY
#define NJOY_ACETK_BLOCK_TABULATEDFISSIONMULTIPLICITY

// system includes

// other includes
#include "ACEtk/block/Base.hpp"
#include "ACEtk/block/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated fission multiplicity
 *
 *  The TabulatedFissionMultiplicity class contains the tabulated
 *  representation of the fission multiplicity.
 */
class TabulatedFissionMultiplicity : protected Base {

  /* fields */
  TabulatedData table_;

  /* auxiliary functions */
  #include "ACEtk/block/TabulatedData/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/TabulatedFissionMultiplicity/src/ctor.hpp"

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return this->table_.NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const { return this->NB(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return this->table_.NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return this->table_.INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the number of values
   */
  std::size_t NE() const { return this->table_.NE(); }

  /**
   *  @brief Return the number of values
   */
  std::size_t numberValues() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return this->table_.x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the multiplicities
   */
  auto NU() const { return this->table_.y(); }

  /**
   *  @brief Return the multiplicities
   */
  auto multiplicities() const { return this->NU(); }

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
