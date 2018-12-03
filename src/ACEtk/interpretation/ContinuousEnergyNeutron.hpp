class ContinuousEnergyNeutron {
  const Table& table;

protected:

  using Slice = Table::Slice;

public:
  ContinuousEnergyNeutron( const Table& table ): table( table ) {}

  int size() const { return this->table.data.NXS(1); }
  int ZA() const { return this->table.data.NXS(2); }


  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder.hpp"
};
