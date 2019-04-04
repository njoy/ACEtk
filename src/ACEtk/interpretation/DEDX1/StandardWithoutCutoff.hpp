class StandardWithoutCutoff : public CRTP<StandardWithoutCutoff> {
  friend CRTP<StandardWithoutCutoff>;
  static constexpr int startOfStoppingPower(){ return 3;}

public:
  StandardWithoutCutoff(const Table& table)
    : CRTP<StandardWithoutCutoff>(table) {}
  StandardWithoutCutoff(Table&&) = delete;  
};
