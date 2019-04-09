struct Law2Int{
  int operator()( const TabularEquiprobableEnergyBins&   ){ return 1; }
  int operator()( const DiscretePhotonEnergy&            ){ return 2; }
  int operator()( const LevelScattering&                 ){ return 3; }
  int operator()( const ContinuousTabularDistribution&   ){ return 4; }
  int operator()( const GeneralEvaporationSpectrum&      ){ return 5; }
  int operator()( const SimpleMaxwellianFissionSpectrum& ){ return 7; }
  int operator()( const EvaporationSpectrum&             ){ return 9; }
  int operator()( const EnergyDependentWattSpectrum&     ){ return 11; }
  int operator()( const TabularLinearFunctions&          ){ return 22; }
  int operator()( const TabularEnergyMultipliers&        ){ return 24; }
  int operator()( const KalbachMann&                     ){ return 44; }
  int operator()( const KalbachMannAngularDistribution&  ){ return 61; }
  int operator()( const NBodyPhaseSpace&                 ){ return 66; }
  int operator()( const LaboratoryAngleEnergy&           ){ return 67; }
};
