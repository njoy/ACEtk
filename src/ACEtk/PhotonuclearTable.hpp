#ifndef NJOY_ACETK_PHOTONUCLEARTABLE
#define NJOY_ACETK_PHOTONUCLEARTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/photonuclear/PrincipalCrossSectionBlock.hpp"
#include "ACEtk/continuous/ReactionNumberBlock.hpp"
#include "ACEtk/continuous/ReactionQValueBlock.hpp"
#include "ACEtk/continuous/CrossSectionBlock.hpp"
#include "ACEtk/photonuclear/SecondaryParticleLocatorBlock.hpp"
#include "ACEtk/continuous/CrossSectionData.hpp"
#include "ACEtk/continuous/FrameAndMultiplicityBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleProductionCrossSectionBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleAngularDistributionBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleEnergyDistributionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The photonuclear ACE table
 *
 *  The PhotonuclearTable class represents the ACE table for the photonuclear data.
 */
class PhotonuclearTable : protected Table {

  /* fields */
  photonuclear::ESZU eszu_;
  continuous::MTR mtr_;
  continuous::LQR lqr_;
  continuous::SIG sig_;

  std::optional< photonuclear::IXSU > ixsu_;
  std::vector< continuous::CrossSectionData > pxs_;
  std::vector< continuous::CrossSectionData > phn_;
  std::vector< continuous::MTRH > mtrh_;
  std::vector< continuous::TYRH > tyrh_;
  std::vector< continuous::SIGH > sigh_;
  std::vector< continuous::ANDH > andh_;
  std::vector< continuous::DLWH > dlwh_;

  /* auxiliary functions */
  #include "ACEtk/PhotonuclearTable/src/generateBlocks.hpp"
  #include "ACEtk/PhotonuclearTable/src/generateData.hpp"
  #include "ACEtk/PhotonuclearTable/src/verifyType.hpp"

public:

  #include "ACEtk/PhotonuclearTable/src/ctor.hpp"

  using Table::header;
  using Table::data;
  using Table::print;

  //! @todo projectile() function
  //! @todo target() function

  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.ZAID(); },
                       this->header() );
  }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.AWR(); },
                       this->header() );
  }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->AWR(); }

  /**
   *  @brief Return the temperature of the table
   */
  double TEMP() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.TEMP(); },
                       this->header() );
  }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->TEMP(); }

  /**
   *  @brief Return the date
   */
  const std::string& date() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.date(); },
                       this->header() );
  }

  // NXS information

  /**
   *  @brief Return the total length of the XSS array
   */
  unsigned int length() const { return this->data().NXS(1); }

  /**
   *  @brief Return the ZA of the target
   */
  unsigned int ZA() const { return this->data().NXS(2); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->data().NXS(3); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const { return this->NTR(); }

  /**
   *  @brief Return the number of secondary particle types
   */
  unsigned int NTYPE() const { return this->data().NXS(5); }

  /**
   *  @brief Return the number of secondary particle types
   */
  unsigned int numberSecondaryParticleTypes() const { return this->NTYPE(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the principal cross section block
   */
  const photonuclear::ESZU& ESZ() const { return this->eszu_; }

  /**
   *  @brief Return the principal cross section block
   */
  const photonuclear::ESZU& principalCrossSectionBlock() const { return this->ESZ(); }

  /**
   *  @brief Return the reaction number block
   */
  const continuous::MTR& MTR() const { return this->mtr_; }

  /**
   *  @brief Return the reaction number block
   */
  const continuous::MTR& reactionNumberBlock() const { return this->MTR(); }

  /**
   *  @brief Return the reaction Q value block
   */
  const continuous::LQR& LQR() const { return this->lqr_; }

  /**
   *  @brief Return the reaction Q value block
   */
  const continuous::LQR& reactionQValueBlock() const { return this->LQR(); }

  /**
   *  @brief Return the cross section block
   */
  const continuous::SIG& SIG() const { return this->sig_; }

  /**
   *  @brief Return the cross section block
   */
  const continuous::SIG& crossSectionBlock() const { return this->SIG(); }

  /**
   *  @brief Return the secondary particle information and locator block
   */
  const std::optional< photonuclear::IXSU >& IXS() const { return this->ixsu_; }

  /**
   *  @brief Return the secondary particle information and locator block
   */
  const std::optional< photonuclear::IXSU >& secondaryParticleLocatorBlock() const {

    return this->IXS();
  }

  /**
   *  @brief Return the secondary particle production cross section for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::CrossSectionData& PXS( std::size_t index ) const {

    return this->pxs_[ index - 1 ];
  }

  /**
   *  @brief Return the secondary particle production cross section for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::CrossSectionData&
  secondaryParticleProductionCrossSection( std::size_t index ) const {

    return this->PXS( index );
  }

  /**
   *  @brief Return the secondary particle average heating cross section for a
   *         secondary particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::CrossSectionData& PHN( std::size_t index ) const {

    return this->phn_[ index - 1 ];
  }

  /**
   *  @brief Return the secondary particle average heating cross section for a
   *         secondary particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::CrossSectionData&
  secondaryParticleHeatingCrossSection( std::size_t index ) const {

    return this->PHN( index );
  }

  /**
   *  @brief Return the reaction number block for a secondary particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::MTRH& MTRH( std::size_t index ) const {

    return this->mtrh_[ index - 1 ];
  }

  /**
   *  @brief Return the reaction number block for a secondary particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::MTRH& secondaryParticleReactionNumberBlock( std::size_t index ) const {

    return this->MTRH( index );
  }

  /**
   *  @brief Return the multiplicity and reference frame block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::TYRH& TYRH( std::size_t index ) const {

    return this->tyrh_[ index - 1 ];
  }

  /**
   *  @brief Return the multiplicity and reference frame block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::TYRH& secondaryParticleFrameAndMultiplicityBlock( std::size_t index ) const {

    return this->TYRH( index );
  }

  /**
   *  @brief Return the production cross section block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::SIGH& SIGH( std::size_t index ) const {

    return this->sigh_[ index - 1 ];
  }

  /**
   *  @brief Return the production cross section block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::SIGH& secondaryParticleProductionCrossSectionBlock( std::size_t index ) const {

    return this->SIGH( index );
  }

  /**
   *  @brief Return the angular distribution block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::ANDH& ANDH( std::size_t index ) const {

    return this->andh_[ index - 1 ];
  }

  /**
   *  @brief Return the angular distribution block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::ANDH& secondaryParticleAngularDistributionBlock( std::size_t index ) const {

    return this->ANDH( index );
  }

  /**
   *  @brief Return the energy distribution block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::DLWH& DLWH( std::size_t index ) const {

    return this->dlwh_[ index - 1 ];
  }

  /**
   *  @brief Return the energy distribution block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::DLWH& secondaryParticleEnergyDistributionBlock( std::size_t index ) const {

    return this->DLWH( index );
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
