#ifndef NJOY_ACETK_PHOTOATOMIC_FLUORESCENCEDATABLOCK
#define NJOY_ACETK_PHOTOATOMIC_FLUORESCENCEDATABLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic JFLO block with the fluorescence data
 *
 *  The FluorescenceDataBlock class contains 4 arrays of the
 *  same length:
 *    - the fluoresence edge energies
 *    - the relative ejection probabilities
 *    - the yields
 *    - the fluorescent energies
 *
 *  The size of each (the total number of fluorescence edges) is stored in NXS(4).
 */
class FluorescenceDataBlock : protected block::details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/photoatomic/FluorescenceDataBlock/src/ctor.hpp"

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int NFLO() const { return this->N(); }

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int numberFluorescenceEdges() const { return this->NFLO(); }

  /**
   *  @brief Return the fluoresence edge energies
   */
  auto E() const { return this->darray( 1 ); }

  /**
   *  @brief Return the fluoresence edge energies
   */
  auto fluorescenceEdgeEnergies() const { return this->E(); }

  /**
   *  @brief Return the relative ejection probabilities
   */
  auto PHI() const { return this->darray( 2 ); }

  /**
   *  @brief Return the relative ejection probabilities
   */
  auto relativeEjectionProbabilities() const { return this->PHI(); }

  /**
   *  @brief Return the yields
   */
  auto Y() const { return this->darray( 3 ); }

  /**
   *  @brief Return the yields
   */
  auto yields() const { return this->Y(); }

  /**
   *  @brief Return the fluorescent energies
   */
  auto F() const { return this->darray( 4 ); }

  /**
   *  @brief Return the fluorescent energies
   */
  auto fluorescentEnergies() const { return this->F(); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using JFLO = FluorescenceDataBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
