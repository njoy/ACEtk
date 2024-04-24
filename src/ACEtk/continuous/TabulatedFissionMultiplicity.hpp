#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDFISSIONMULTIPLICITY
#define NJOY_ACETK_CONTINUOUS_TABULATEDFISSIONMULTIPLICITY

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Tabulated fission multiplicity
 *
 *  The TabulatedFissionMultiplicity class contains the tabulated
 *  representation (LNU = 2) of the fission multiplicity. It is
 *  used in the NU block.
 */
class TabulatedFissionMultiplicity : protected base::Base {

  /* fields */
  base::TabulatedData data_;

  /* auxiliary functions */
  #include "ACEtk/continuous/TabulatedFissionMultiplicity/src/generateXSS.hpp"
  #include "ACEtk/continuous/TabulatedFissionMultiplicity/src/generateBlocks.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/TabulatedFissionMultiplicity/src/ctor.hpp"

  /**
   *  @brief Return the representation type (should always be 2)
   */
  unsigned int LNU() const {

    return static_cast< unsigned int >( this->IXSS( 1 ) );
  }

  /**
   *  @brief Return the representation type (should always be 2)
   */
  std::size_t type() const { return this->LNU(); }

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
   *  @brief Return the multiplicities
   */
  auto NU() const { return this->data_.y(); }

  /**
   *  @brief Return the multiplicities
   */
  auto multiplicities() const { return this->NU(); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
