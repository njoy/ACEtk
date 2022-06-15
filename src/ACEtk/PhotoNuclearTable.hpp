#ifndef NJOY_ACETK_PHOTONUCLEARTABLE
#define NJOY_ACETK_PHOTONUCLEARTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/block/PhotoNuclearPrincipalCrossSectionBlock.hpp"
#include "ACEtk/block/ReactionNumberBlock.hpp"
#include "ACEtk/block/ReactionQValueBlock.hpp"
#include "ACEtk/block/CrossSectionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The photonuclear ACE table
 *
 *  The PhotoAtomicTable class represents the ACE table for the photonuclear data.
 */
class PhotoNuclearTable : protected Table {

  /* fields */
  block::ESZU eszu_;
  block::MTR mtr_;
  block::LQR lqr_;
  block::SIG sig_;

  /* auxiliary functions */
  #include "ACEtk/PhotoNuclearTable/src/generateBlocks.hpp"
//  #include "ACEtk/PhotoNuclearTable/src/generateData.hpp"

public:

  #include "ACEtk/PhotoNuclearTable/src/ctor.hpp"

  using Table::header;
  using Table::data;
  using Table::print;

  //! @todo projectile() function
  //! @todo target() function

  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const { return this->header().ZAID(); }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const { return this->header().AWR(); }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->header().atomicWeightRatio(); }

  /**
   *  @brief Return the temperature of the table
   */
  double TEMP() const { return this->header().TEMP(); }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->header().temperature(); }

  /**
   *  @brief Return the date
   */
  const std::string& date() const { return this->header().date(); }

  /**
   *  @brief Return the title
   */
  const std::string& title() const { return this->header().title(); }

  /**
   *  @brief Return the material
   */
  const std::string& material() const { return this->header().material(); }

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
  const block::ESZU& ESZ() const { return this->eszu_; }

  /**
   *  @brief Return the principal cross section block
   */
  const block::ESZU& principalCrossSectionBlock() const { return this->ESZ(); }

  /**
   *  @brief Return the reaction number block
   */
  const block::MTR& MTR() const { return this->mtr_; }

  /**
   *  @brief Return the reaction number block
   */
  const block::MTR& reactionNumberBlock() const { return this->MTR(); }

  /**
   *  @brief Return the reaction Q value block
   */
  const block::LQR& LQR() const { return this->lqr_; }

  /**
   *  @brief Return the reaction Q value block
   */
  const block::LQR& reactionQValueBlock() const { return this->LQR(); }

  /**
   *  @brief Return the cross section block
   */
  const block::SIG& SIG() const { return this->sig_; }

  /**
   *  @brief Return the cross section block
   */
  const block::SIG& crossSectionBlock() const { return this->SIG(); }
};

} // ACEtk namespace
} // njoy namespace

#endif