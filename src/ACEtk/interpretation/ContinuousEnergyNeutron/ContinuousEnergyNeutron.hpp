class ContinuousEnergyNeutron {
  const Table& table;

public:
  ContinuousEnergyNeutron( const Table& table ): table( table ) {}

  int size() const { return this->table.data.NXS(1); }
  int ZA() const { return this->table.data.NXS(2); }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/ContinuousEnergyNeutron/EnergyGrid.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/ContinuousEnergyNeutron/src/neutronReactionIDs.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/ContinuousEnergyNeutron/src/photonProductionReactionIDs.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/ContinuousEnergyNeutron/src/reactionIDs.hpp"

};
