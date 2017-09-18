struct El03 {

  struct RadiativeStopping{
    static constexpr size_t energyGridBegin = 2;
    static constexpr size_t energyGridLength = 3;
    static constexpr size_t begin = 2;
    static constexpr size_t length = 3;
    static constexpr size_t offset = 1;
    static constexpr auto independentVariableUnits = 1.0 * mega( electronVolts );
    static constexpr auto dependentVariableUnits = 1.0 * constant::unitless;        
  };

  struct BremsstrahlungCorrection{
    static constexpr size_t begin = 2;
    static constexpr size_t length = 3;
    static constexpr size_t offset = 2;    
    static constexpr auto dependentVariableUnits = 1.0 * constant::unitless;        
  };  

};

