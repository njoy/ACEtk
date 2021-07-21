#ifndef NJOY_ACETK_CONTINUOUSENERGYTABLE
#define NJOY_ACETK_CONTINUOUSENERGYTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"

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

public:

  #include "ACEtk/ContinuousEnergyTable/src/ctor.hpp"

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
};

} // ACEtk namespace
} // njoy namespace

#endif
