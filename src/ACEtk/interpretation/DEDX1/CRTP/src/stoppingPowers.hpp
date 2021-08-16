template<typename... T>
static void f(T...){std::puts(__PRETTY_FUNCTION__);}

auto stoppingPowers() const {
  // lift into protected method
  auto logStoppingPowerRanges = [&self = *this]{
    const auto& derived = static_cast<const Derived&>( self );
    const auto& table = self.table.get();

    const auto start = table.data().JXS( derived.startOfStoppingPower() );
    const auto length =
      self.numEnergies() * self.numDensities() * self.numTemperatures();

    return
      table.data().XSS( start, length )
      | ranges::views::chunk( self.numEnergies() );
  }();

  using LogEnergies = decltype(this->logEnergies());
  using LogValues = std::decay_t<decltype(logStoppingPowerRanges.front())>;

  // lift into protected class
  class StoppingPower {
    double logTemperature_;
    double logDensity_;
    LogEnergies logEnergies_;
    LogValues logValues_;
  public:
    StoppingPower(double logT, double logD, LogEnergies logE, LogValues logV)
      : logTemperature_(logT), logDensity_(logD), logEnergies_(logE), logValues_(logV)
    {}
    auto logTemperature() const {return this->logTemperature_;}
    auto temperature() const {return std::exp(this->logTemperature()) * mev;}
    auto logDensity() const {return this->logDensity_;}
    auto density() const {return std::exp(this->logDensity()) / cc;}
    auto logEnergies() const {return this->logEnergies_;}
    auto energies() const {
      return this->logEnergies()
	| ranges::cpp20::views::transform([](auto&& e){ return std::exp(e) * mev;});
    }
    auto logValues() const {return this->logValues_;}
    auto values() const {
      return this->logValues() |
	ranges::cpp20::views::transform([](auto&& v){ return std::exp(v) * (cm*cm*mev);});
    }
  };

  auto makeStoppingPower = [=](auto&& tup, auto&& rangeLogValues){
    auto logTemperature = std::get<0>(tup);
    auto logDensity = std::get<1>(tup);
    return StoppingPower{logTemperature, logDensity, this->logEnergies(), rangeLogValues};
  };

  auto densAndTemps = ranges::views::cartesian_product(this->logTemperatures(),
						      this->logDensities());

  auto stoppingPowerRange = ranges::views::zip_with(makeStoppingPower,
						   densAndTemps,
						   logStoppingPowerRanges);

  return stoppingPowerRange;
}
