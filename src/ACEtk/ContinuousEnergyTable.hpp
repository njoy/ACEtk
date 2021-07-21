#ifndef NJOY_ACETK_CONTINUOUSENERGYTABLE
#define NJOY_ACETK_CONTINUOUSENERGYTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"

namespace njoy {
namespace ACEtk {

class ContinuousEnergyTable : public Table {

public:

  ContinuousEnergyTable( Table&& table ): Table( std::move( table ) ) {}

  int size() const { return this->data().NXS(1); }
  int ZA() const { return this->data().NXS(2); }
};

} // ACEtk namespace
} // njoy namespace

#endif
