#ifndef NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy GPD block with the total photon production
 *         cross section
 *
 *  The PhotonProductionBlock class contains the total photon production cross
 *  section, given on the same energy grid as defined in the principal cross
 *  section block. For older data files, this also contains the equiprobable
 *  energy bins.
 */
class PhotonProductionBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  PhotonProductionBlock() = default;

  PhotonProductionBlock( const PhotonProductionBlock& ) = default;
  PhotonProductionBlock( PhotonProductionBlock&& ) = default;

  PhotonProductionBlock& operator=( const PhotonProductionBlock& ) = default;
  PhotonProductionBlock& operator=( PhotonProductionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] production    the total photon production cross section values
   */
  PhotonProductionBlock( std::vector< double > production ) :
    ArrayData( "GPD",
               std::vector< std::vector< double > >{ std::move( production ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the GPD block in the XSS array
   *  @param[in] end     the end iterator of the GPD block in the XSS array
   *  @param[in] nes     the number of energy points
   */
  PhotonProductionBlock( Iterator begin, Iterator end, unsigned int nes ) :
    ArrayData( "GPD", begin, end, nes, 1 ) {}

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
   *  @brief Return the total photon production cross section values
   */
  auto totalProduction() const { return this->darray( 1 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using GPD = PhotonProductionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
