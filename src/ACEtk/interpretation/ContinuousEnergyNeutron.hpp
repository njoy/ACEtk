class ContinuousEnergyNeutron {
  const Table& table;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/NeutronHeaderIndices.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/PhotonProductionHeaderIndices.hpp"

  using Slice = decltype( table.data.XSS( 1, 2 ) );

public:
  ContinuousEnergyNeutron( const Table& table ): table( table ) {}

  int ZA() const { return this->table.data.NXS(2); }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/fissionMultiplicity.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/angularDistribution.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/CrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyGrid.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Reaction.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/neutronReactionIDs.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/photonProductionReactionIDs.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/reactionIDs.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/reactionIndex.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/QValues.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/makeCrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/src/makeReaction.hpp"


};

typedef ContinuousEnergyNeutron nc;
