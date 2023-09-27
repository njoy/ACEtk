#ifndef NJOY_ACETK_BLOCK_PHOTOATOMICELECTRONELASTICCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_PHOTOATOMICELECTRONELASTICCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic SELAS block with the additional electron elastic
 *         cross section data
 *
 *  This block is part of the eprdata14 format.
 *
 *  The PhotoatomicElectronElasticCrossSectionBlock class contains 2 arrays
 *  of the same length:
 *    - the transport elastic scattering cross section
 *    - the total elastic scattering cross section
 *
 *  The size NE of each (the total number of electron energy points) is stored in
 *  NXS(8).
 */
class PhotoatomicElectronElasticCrossSectionBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/PhotoatomicElectronElasticCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NE() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the transport elastic cross section values
   */
  auto transport() const { return this->darray( 1 ); }

  /**
   *  @brief Return the total elastic cross section values
   */
  auto total() const { return this->darray( 2 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using SELAS = PhotoatomicElectronElasticCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif