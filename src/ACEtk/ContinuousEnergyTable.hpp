#ifndef NJOY_ACETK_CONTINUOUSENERGYTABLE
#define NJOY_ACETK_CONTINUOUSENERGYTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/block/PrincipalCrossSectionBlock.hpp"

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

  /* auxiliary functions */
  void generateBlocks() {

    auto begin = this->data().XSS().begin();
    auto esz = begin + this->data().JXS(1);
    auto nu = begin + this->data().JXS(2);
    auto mtr = begin + this->data().JXS(3);
    auto lqr = begin + this->data().JXS(4);
    auto tyr = begin + this->data().JXS(5);
    auto lsig = begin + this->data().JXS(6);
    auto sig = begin + this->data().JXS(7);
    auto land = begin + this->data().JXS(8);
    auto and_ = begin + this->data().JXS(9);
    auto ldlw = begin + this->data().JXS(10);
    auto dlw = begin + this->data().JXS(11);

    this->esz_ = block::ESZ( esz, this->data().JXS(2) > 0 ? nu : mtr, this->NES() );
  }

public:

  #include "ACEtk/ContinuousEnergyTable/src/ctor.hpp"

  using Table::header;
  using Table::data;
  using Table::print;

  //! @todo projectile() function
  //! @todo target() function

  // NXS information

  /**
   *  @brief Return the total length of the XSS array
   */
  int length() const { return this->data().NXS(1); }

  /**
   *  @brief Return the ZA of the target
   */
  int ZA() const { return this->data().NXS(2); }

  /**
   *  @brief Return the number of energy points
   */
  int NES() const { return this->data().NXS(3); }

  /**
   *  @brief Return the number of energy points
   */
  int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the number of reactions excluding elastic
   */
  int NTR() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of reactions excluding elastic
   */
  int numberReactionsExcludingElastic() const { return this->NTR(); }

  /**
   *  @brief Return the number of reactions excluding elastic that produce the
   *         projectile
   */
  int NR() const { return this->data().NXS(5); }

  /**
   *  @brief Return the number of reactions excluding elastic that produce the
   *         projectile
   */
  int numberProjectileProductionReactionsExcludingElastic() const { return this->NR(); }

  /**
   *  @brief Return the number of reactions that produce photons
   */
  int NTRP() const { return this->data().NXS(6); }

  /**
   *  @brief Return the number of reactions that produce photons
   */
  int numberPhotonProductionReactions() const { return this->NTRP(); }

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile)
   */
  int NTYPE() const { return this->data().NXS(7); }

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile)
   */
  int numberAdditionalSecondaryParticleTypes() const { return this->NTYPE(); }

  /**
   *  @brief Return the number of delayed percursor families
   */
  int NPCR() const { return this->data().NXS(8); }

  /**
   *  @brief Return the number of delayed percursor families
   */
  int numberDelayedPrecursors() const { return this->NPCR(); }

  /**
   *  @brief Return the excited state of the target
   */
  int S() const { return this->data().NXS(9); }

  /**
   *  @brief Return the excited state of the target
   */
  int excitedState() const { return this->S(); }

  /**
   *  @brief Return the atom number of the target
   */
  int Z() const { return this->data().NXS(10); }

  /**
   *  @brief Return the atom number of the target
   */
  int atomNumber() const { return this->Z(); }

  /**
   *  @brief Return the mass number of the target
   */
  int A() const { return this->data().NXS(11); }

  /**
   *  @brief Return the mass number of the target
   */
  int massNumber() const { return this->A(); }

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
};

} // ACEtk namespace
} // njoy namespace

#endif
