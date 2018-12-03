class Builder {
private:

  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  std::reference_wrapper< ParentBuilder > parent;

public:
  Builder( ParentBuilder& parent ): parent( parent ) { }

  Polynomial::Builder polynomial(){ return Polynomial::Builder{ parent }; }
  Tabulated::Builder tabulated(){ return Tabulated::Builder{ parent }; }
};
