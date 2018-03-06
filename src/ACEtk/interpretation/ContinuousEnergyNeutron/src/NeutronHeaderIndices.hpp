struct NeutronHeaderIndices{
  static constexpr HeaderIndices Energies{ 3, 1 };
  static constexpr HeaderIndices MTs{ 4, 3 };
  static constexpr HeaderIndices QValues{ 4, 4};
  static constexpr HeaderIndices crossSection{ 4, 7};

  struct Locators{
    static constexpr HeaderIndices crossSection{ 4, 6 };
  };
};

