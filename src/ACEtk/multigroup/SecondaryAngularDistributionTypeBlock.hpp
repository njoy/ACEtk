#ifndef NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLETYPEBLOCK
#define NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLETYPEBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup SANG2 block with the secondary particle angular distribution types
 *
 *  The SecondaryAngularDistributionTypeBlock class contains the secondary angular distribution 
 *  types. The allowed particle types are:
 *      0  -  equi-probable cosines
 *      1  -  discrete cosines
 *
 *  The number of particle types (NSEC) is stored in NXS(8).
 */
class SecondaryAngularDistributionTypeBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/multigroup/SecondaryAngularDistributionTypeBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of secondary particles
   */
  unsigned int NSEC() const { return this->N(); }

  /**
   *  @brief Return the number of secondary particles 
   */
  unsigned int numberSecondaryParticles() const {

    return this->NSEC();
  }

  /**
   *  @brief Return the angular distribution type for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int SANG2( std::size_t index ) const { return this->ivalue( 1, index ); }

  /**
   *  @brief Return the angular distribution type for a secondary particle index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int distributionType( std::size_t index ) const {

    return this->SANG2( index );
  }

  /**
   *  @brief Return the angular distribution types
   */
  auto SANG2s() const { return this->iarray( 1 ); }

  /**
   *  @brief Return the angular distribution types
   */
  auto distributionTypes() const { return this->SANG2s(); }


  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using SANG2 = SecondaryAngularDistributionTypeBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
