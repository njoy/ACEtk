#ifndef NJOY_ACETK_BLOCK_PHOTOELECTRICCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_PHOTOELECTRICCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic SPHEL block with the photoelectric cross section for
 *         each subshell
 *
 *  This block is part of the eprdata formats.
 *
 *  The PhotoelectricCrossSectionBlock class contains NSSH arrays
 *  of the same length, each one being the photoelectric cross section of a
 *  subshell.
 *
 *  The size of each (the total number of energy points NES) is stored in NXS(3).
 */
class PhotoelectricCrossSectionBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/PhotoelectricCrossSectionBlock/src/verifyIndex.hpp"

public:

  /* constructor */
  #include "ACEtk/block/PhotoelectricCrossSectionBlock/src/ctor.hpp"

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
   *  @brief Return the number of electron subshells
   */
  unsigned int NSSH() const { return this->M(); }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronSubshells() const { return this->NSSH(); }

  /**
   *  @brief Return the photoelectric cross section values for a specific shell
   *
   *  @param[in] index    the electron subshell index (one-based)
   */
  auto photoelectric( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( index );
    #endif
    return this->darray( index );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using SPHEL = PhotoelectricCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
