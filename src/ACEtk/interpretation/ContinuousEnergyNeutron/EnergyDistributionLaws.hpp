#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/BaseLaw.hpp"   

#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/TabularEquiprobableEnergyBins.hpp"    // Law 1
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/DiscretePhotonEnergy.hpp"             // Law 2

#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/ContinuousTabular.hpp"                // Law 4
#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/GeneralEvaporationSpectrum.hpp"       // Law 5

#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/SimpleMaxwellFissionSpectrum.hpp"     // Law 7

#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/EvaporationSpectrum.hpp"              // Law 9

#include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/EnergyDependentWattSpectrum.hpp"      // Law 11
