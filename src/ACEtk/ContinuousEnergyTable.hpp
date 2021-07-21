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
class ContinuousEnergyTable : public Table {

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

  //! @todo projectile() function
  //! @todo target() function

  // NXS information
  int length() const { return this->data().NXS(1); }
  int ZA() const { return this->data().NXS(2); }
  int NES() const { return this->data().NXS(3); }
  int numberEnergyPoints() const { return this->NES(); }
  int NTR() const { return this->data().NXS(4); }
  int numberReactionsExcludingElastic() const { return this->NTR(); }
  int NR() const { return this->data().NXS(5); }
  int numberProjectileProductionReactionsExcludingElastic() const { return this->NR(); }
  int NTRP() const { return this->data().NXS(6); }
  int numberPhotonProductionReactions() const { return this->NTRP(); }
  int NTYPE() const { return this->data().NXS(7); }
  int numberAdditionalSecondaryParticleTypes() const { return this->NTYPE(); }
  int NPCR() const { return this->data().NXS(8); }
  int numberDelayedPrecursors() const { return this->NPCR(); }
  int S() const { return this->data().NXS(9); }
  int excitedState() const { return this->S(); }
  int Z() const { return this->data().NXS(10); }
  int atomNumber() const { return this->Z(); }
  int A() const { return this->data().NXS(11); }
  int massNumber() const { return this->A(); }

  // JXS information

  // XSS blocks
  const block::ESZ& ESZ() const { return this->esz_; }
  const block::ESZ& principalCrossSectionBlock() const { return this->ESZ(); }

};

} // ACEtk namespace
} // njoy namespace

#endif
