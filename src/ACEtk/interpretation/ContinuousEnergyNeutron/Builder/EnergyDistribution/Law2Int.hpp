struct Law2Int{
  constexpr int operator()( const TabularEquiprobableEnergyBins&   ) const { return 1; }
  constexpr int operator()( const DiscretePhotonEnergy&            ) const { return 2; }
  constexpr int operator()( const LevelScattering&                 ) const { return 3; }
  constexpr int operator()( const ContinuousTabularDistribution&   ) const { return 4; }
  constexpr int operator()( const GeneralEvaporationSpectrum&      ) const { return 5; }
  constexpr int operator()( const SimpleMaxwellianFissionSpectrum& ) const { return 7; }
  constexpr int operator()( const EvaporationSpectrum&             ) const { return 9; }
  constexpr int operator()( const EnergyDependentWattSpectrum&     ) const { return 11; }
  constexpr int operator()( const TabularLinearFunctions&          ) const { return 22; }
  constexpr int operator()( const TabularEnergyMultipliers&        ) const { return 24; }
  constexpr int operator()( const KalbachMann&                     ) const { return 44; }
  constexpr int operator()( const KalbachMannAngularDistribution&  ) const { return 61; }
  constexpr int operator()( const NBodyPhaseSpace&                 ) const { return 66; }
  constexpr int operator()( const LaboratoryAngleEnergy&           ) const { return 67; }
};
