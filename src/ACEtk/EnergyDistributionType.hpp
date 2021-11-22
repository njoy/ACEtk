#ifndef NJOY_ACETK_ENERGYDISTRIBUTIONTYPE
#define NJOY_ACETK_ENERGYDISTRIBUTIONTYPE

// system includes

// other includes

namespace njoy {
namespace ACEtk {

  enum class EnergyDistributionType : short {

    Equiprobable = 1,            // ACE LAW = 1 - equiprobable bins
    DiscretePhoton = 2,          // ACE LAW = 2 - discrete photon
    LevelScattering = 3,         // ACE LAW = 3 - level scattering distribution
    TabulatedEnergy = 4,         // ACE LAW = 4 - tabulated E,Eprime
    GeneralEvaporation = 5,      // ACE LAW = 5 - general evaporation spectrum
    SimpleMaxwellianFission = 7, // ACE LAW = 7 - simple Maxwellian fission spectrum
    Evaporation = 9,             // ACE LAW = 9 - evaporation spectrum
    Watt = 11,                   // ACE LAW = 11 - energy dependent Watt spectrum
    XXXXX = 33,                  // ACE LAW = 33 - xxxx
    KalbachMann = 44,            // ACE LAW = 44 - Kalbach-Mann systematics
    TabulatedEnergyAngle = 61,   // ACE LAW = 61 - tabulated E,Eprime,mu
    NBodyPhaseSpace = 66,        // ACE LAW = 66 - N-body phase space
    TabulatedAngleEnergy = 67    // ACE LAW = 67 - tabulated E,mu,Eprime
  };

} // ACEtk namespace
} // njoy namespace

#endif
