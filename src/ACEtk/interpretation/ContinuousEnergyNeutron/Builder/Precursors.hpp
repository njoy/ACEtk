struct Precursors {
  using ParentBuilder = ContinuousEnergyNeutron::Builder;

  double decayConstant;
  Tabulated1D data;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/Builder.hpp"

  auto ACEify() const {
    auto rData = this->data.ACEify();
    return ranges::view::concat( ranges::view::single( decayConstant ), rData);
  }
};
