class BPS : public CRTP<BPS> {
  friend CRTP<BPS>;
  static constexpr int startOfStoppingPower(){ return 5;}

public:
  BPS(const Table& table)
    : CRTP<BPS>(table) {}
  BPS(Table&&) = delete;  
};
