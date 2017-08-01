struct El03 {

  struct RadiativeStopping{
    static constexpr size_t energyGridBegin = 2;
    static constexpr size_t energyGridLength = 3;
    static constexpr size_t radStoppingPowerBegin = 2;
    static constexpr size_t radStoppingPowerLength = 3;    
    static constexpr auto independentVariableUnits = 1.0 * mega( electronVolts );
    static constexpr auto dependentVariableUnits = 1.0 * constant::unitless;        
  };

};

