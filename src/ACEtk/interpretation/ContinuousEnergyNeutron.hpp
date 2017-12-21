class ContinuousEnergyNeutron {
  const Table& table;

public:
  ContinuousEnergyNeutron( const Table& table ): table( table ) {}

  int size() const { return this->table.data.NXS(1); }
  int ZA() const { return this->table.data.NXS(2); }
};
