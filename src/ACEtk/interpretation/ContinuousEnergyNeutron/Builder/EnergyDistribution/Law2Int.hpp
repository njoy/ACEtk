struct Law2Int{
  int operator()( const TabularEquiprobableEnergyBins&   ) const { return 1; }
  int operator()( const DiscretePhotonEnergy&            ) const { return 2; }
  int operator()( const LevelScattering&                 ) const { return 3; }
  int operator()( const ContinuousTabularDistribution&   ) const { return 4; }
  int operator()( const GeneralEvaporationSpectrum&      ) const { return 5; }
  int operator()( const SimpleMaxwellianFissionSpectrum& ) const { return 7; }
  int operator()( const EvaporationSpectrum&             ) const { return 9; }
  int operator()( const EnergyDependentWattSpectrum&     ) const { return 11; }
  int operator()( const TabularLinearFunctions&          ) const { return 22; }
  int operator()( const TabularEnergyMultipliers&        ) const { return 24; }
  int operator()( const KalbachMann&                     ) const { return 44; }
  int operator()( const KalbachMannAngularDistribution&  ) const { return 61; }
  int operator()( const NBodyPhaseSpace&                 ) const { return 66; }
  int operator()( const LaboratoryAngleEnergy&           ) const { return 67; }
};
