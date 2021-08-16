class StandardWithCutoff : public CRTP<StandardWithCutoff> {
  friend CRTP<StandardWithCutoff>;
  static constexpr int startOfStoppingPower(){ return 4;}

public:
  StandardWithCutoff(const Table& table)
    : CRTP<StandardWithCutoff>(table) {}
  StandardWithCutoff(Table&&) = delete;  
};
