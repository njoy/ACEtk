class Incoherent : public CRTP<Incoherent> {
  friend CRTP<Incoherent>;
protected:
  static constexpr int crossSectionOffset() { return 1; }
  static constexpr int formFactorOffset() { return 0; }    
  static constexpr bool hasCumulativeFormFactor() { return true; }
  static constexpr bool hasCumulative = false;
  
public:
  Incoherent(const Table& table) : CRTP<Incoherent>(table) {}
  Incoherent(Table&&) = delete;  
};
