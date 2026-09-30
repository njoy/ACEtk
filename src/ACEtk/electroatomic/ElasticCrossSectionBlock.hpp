#ifndef NJOY_ACETK_ELECTROATOMIC_ELASTICCROSSSECTIONBLOCK
#define NJOY_ACETK_ELECTROATOMIC_ELASTICCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

/**
 *  @class
 *  @brief The electron SELAS block with the additional electron elastic
 *         cross section data
 *
 *  This block is part of the eprdata14 format.
 *
 *  The ElasticCrossSectionBlock class contains 2 arrays of the same length:
 *    - the transport elastic scattering cross section
 *    - the total elastic scattering cross section
 *
 *  The size NE of each (the total number of electron energy points) is stored in
 *  NXS(8).
 */
class ElasticCrossSectionBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  ElasticCrossSectionBlock() = default;

  ElasticCrossSectionBlock( const ElasticCrossSectionBlock& ) = default;
  ElasticCrossSectionBlock( ElasticCrossSectionBlock&& ) = default;

  ElasticCrossSectionBlock& operator=( const ElasticCrossSectionBlock& ) = default;
  ElasticCrossSectionBlock& operator=( ElasticCrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] transport    the transport elastic cross section values
   *  @param[in] total        the total elastic cross section values
   */
  ElasticCrossSectionBlock(
      std::vector< double > transport,
      std::vector< double > total ) :
    ArrayData( "SELAS", std::move( transport ), std::move( total ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the ESZE block in the XSS array
   *  @param[in] end     the end iterator of the ESZE block in the XSS array
   *  @param[in] nssh    the number of electron shells
   *  @param[in] ne      the number of energy values
   */
  ElasticCrossSectionBlock( Iterator begin, Iterator end,
                                        unsigned int ne ) :
    ArrayData( "SELAS", begin, end, ne, 2 ) {}

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

using SELAS = ElasticCrossSectionBlock;

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
