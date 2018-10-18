class Incoherent : public CRTP<Incoherent> {
  std::reference_wrapper<const Table> table;
  friend CRTP<Incoherent>;
  
protected:
  static constexpr int crossSectionOffset() { return 1; }
  static constexpr int formFactorOffset() { return 0; }    
  static constexpr bool hasCumulativeFormFactor() { return true; }

  static constexpr bool hasCumulative = false;
  
public:
  Incoherent( const Table& table )
    : CRTP<Incoherent>(table), table(table) {}
  
};
