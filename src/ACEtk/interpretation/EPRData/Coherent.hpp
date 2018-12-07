class Coherent : public CRTP<Coherent> {
  friend CRTP<Coherent>;
  
protected:
  static constexpr int crossSectionOffset() { return 2; }
  static constexpr int formFactorOffset() { return 1; }    
  static constexpr bool hasCumulativeFormFactor() { return true; }

public:
  Coherent(const Table& table) : CRTP<Coherent>(table) {}
  Coherent(Table&&) = delete;
};
