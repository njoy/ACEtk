#ifndef NJOY_ACETK_PHOTOATOMIC_HEATINGNUMBERSBLOCK
#define NJOY_ACETK_PHOTOATOMIC_HEATINGNUMBERSBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic LHNM block with the heating numbers
 *
 *  The PhotoatomicHeatingNumbersBlock class contains the heating numbers.
 *  The size of the array is stored in NXS(3) and the corresponding energy
 *  points can be found in the ESZG block.
 */
class PhotoatomicHeatingNumbersBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/photoatomic/HeatingNumbersBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the heating numbers
   */
  auto heating() const { return this->darray( 1 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using LHNM = PhotoatomicHeatingNumbersBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
