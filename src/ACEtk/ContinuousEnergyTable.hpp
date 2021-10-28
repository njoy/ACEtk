#ifndef NJOY_ACETK_CONTINUOUSENERGYTABLE
#define NJOY_ACETK_CONTINUOUSENERGYTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/block/PrincipalCrossSectionBlock.hpp"
#include "ACEtk/block/FissionMultiplicityBlock.hpp"
#include "ACEtk/block/ReactionNumberBlock.hpp"
#include "ACEtk/block/ReactionQValueBlock.hpp"
#include "ACEtk/block/FrameAndMultiplicityBlock.hpp"
#include "ACEtk/block/CrossSectionBlock.hpp"
#include "ACEtk/block/AngularDistributionBlock.hpp"
#include "ACEtk/block/EnergyDistributionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The continuous energy ACE table
 *
 *  The ContinuousEnergyTable class represents the ACE table for continuous
 *  energy data for incident neutrons and charged particles.
 */
class ContinuousEnergyTable : protected Table {

  /* fields */
  block::ESZ esz_;
  block::NU nu_;
  block::MTR mtr_;
  block::LQR lqr_;
  block::TYR tyr_;
  block::SIG sig_;
  block::AND and_;
  block::DLW dlw_;

  /* auxiliary functions */
  void generateBlocks() {

    auto begin = this->data().XSS().begin();
    auto esz = begin + this->data().JXS(1) - 1;
    auto nu = begin + this->data().JXS(2) - 1;
    auto mtr = begin + this->data().JXS(3) - 1;
    auto lqr = begin + this->data().JXS(4) - 1;
    auto tyr = begin + this->data().JXS(5) - 1;
    auto lsig = begin + this->data().JXS(6) - 1;
    auto sig = begin + this->data().JXS(7) - 1;
    auto land = begin + this->data().JXS(8) - 1;
    auto xand = begin + this->data().JXS(9) - 1;
    auto ldlw = begin + this->data().JXS(10) - 1;
    auto dlw = begin + this->data().JXS(11) - 1;

    this->esz_ = block::ESZ( esz, this->data().JXS(2) > 0 ? nu : mtr, this->NES() );
    this->nu_ = block::NU( this->data().JXS(2) > 0 ? nu : mtr, mtr );
    this->mtr_ = block::MTR( mtr, lqr, this->NTR() );
    this->lqr_ = block::LQR( lqr, tyr, this->NTR() );
    this->tyr_ = block::TYR( tyr, lsig, this->NTR() );
    this->sig_ = block::SIG( lsig, sig, land, this->NTR() );
    this->and_ = block::AND( land, xand, ldlw, this->NR() );
    this->dlw_ = block::DLW( ldlw, dlw, this->data().XSS().end(), this->NR() );
  }

public:

  #include "ACEtk/ContinuousEnergyTable/src/ctor.hpp"

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
   *  @brief Return the titla string
   */
  const std::string& title() const { return this->header().title(); }

  /**
   *  @brief Return the material string
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
   *  @brief Return the total number of available reactions (including elastic)
   */
  unsigned int totalNumberReactions() const { return this->NTR() + 1; }

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int NR() const { return this->data().NXS(5); }

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int numberProjectileProductionReactions() const { return this->NR(); }

  /**
   *  @brief Return the number of reactions that produce photons
   */
  unsigned int NTRP() const { return this->data().NXS(6); }

  /**
   *  @brief Return the number of reactions that produce photons
   */
  unsigned int numberPhotonProductionReactions() const { return this->NTRP(); }

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile)
   */
  unsigned int NTYPE() const { return this->data().NXS(7); }

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile)
   */
  unsigned int numberAdditionalSecondaryParticleTypes() const { return this->NTYPE(); }

  /**
   *  @brief Return the number of delayed percursor families
   */
  unsigned int NPCR() const { return this->data().NXS(8); }

  /**
   *  @brief Return the number of delayed percursor families
   */
  unsigned int numberDelayedPrecursors() const { return this->NPCR(); }

  /**
   *  @brief Return the excited state of the target
   */
  unsigned int S() const { return this->data().NXS(9); }

  /**
   *  @brief Return the excited state of the target
   */
  unsigned int excitedState() const { return this->S(); }

  /**
   *  @brief Return the atom number of the target
   */
  unsigned int Z() const { return this->data().NXS(10); }

  /**
   *  @brief Return the atom number of the target
   */
  unsigned int atomNumber() const { return this->Z(); }

  /**
   *  @brief Return the mass number of the target
   */
  unsigned int A() const { return this->data().NXS(11); }

  /**
   *  @brief Return the mass number of the target
   */
  unsigned int massNumber() const { return this->A(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the principal cross section block
   */
  const block::ESZ& ESZ() const { return this->esz_; }

  /**
   *  @brief Return the principal cross section block
   */
  const block::ESZ& principalCrossSectionBlock() const { return this->ESZ(); }

  /**
   *  @brief Return the fission multiplicity block
   */
  const block::NU& NU() const { return this->nu_; }

  /**
   *  @brief Return the fission multiplicity block
   */
  const block::NU& fissionMultiplicityBlock() const { return this->NU(); }

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
   *  @brief Return the reference frame and multiplicity block
   */
  const block::TYR& TYR() const { return this->tyr_; }

  /**
   *  @brief Return the reference frame and multiplicity block
   */
  const block::TYR& frameAndMultiplicityBlock() const { return this->TYR(); }

  /**
   *  @brief Return the cross section block
   */
  const block::SIG& SIG() const { return this->sig_; }

  /**
   *  @brief Return the cross section block
   */
  const block::SIG& crossSectionBlock() const { return this->SIG(); }

  /**
   *  @brief Return the angular distribution block
   */
  const block::AND& AND() const { return this->and_; }

  /**
   *  @brief Return the angular distribution block
   */
  const block::AND& angularDistributionBlock() const { return this->AND(); }

  /**
   *  @brief Return the energy distribution block
   */
  const block::DLW& DLW() const { return this->dlw_; }

  /**
   *  @brief Return the energy distribution block
   */
  const block::DLW& energyDistributionBlock() const { return this->DLW(); }
};

} // ACEtk namespace
} // njoy namespace

#endif
