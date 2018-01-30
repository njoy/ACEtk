class EnergyGrid {
  const Table& table;

public:
  EnergyGrid( const Table& table ) : table( table ) {}

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyGrid/src/energies.hpp"

  int size() const {
    return this->table.data.NXS( 3 );
  }
};
