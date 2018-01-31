class ContinuousEnergyNeutron {
  const Table& table;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Reaction.hpp"

protected:
  using Slice = decltype( table.data.XSS( 1, 2 ) );

public:
  ContinuousEnergyNeutron( const Table& table ): table( table ) {}

  int size() const { return this->table.data.NXS(1); }
  int ZA() const { return this->table.data.NXS(2); }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/CrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyGrid.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/neutronReactionIDs.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/photonProductionReactionIDs.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/reactionIDs.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Reaction/Neutron.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Reaction/PhotonProduction.hpp"

};

typedef ContinuousEnergyNeutron nc;
