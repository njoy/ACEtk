auto stoppingPowers() const {
  // lift into protected method
  auto logStoppingPowerRanges = [=]{
    const auto& derived = static_cast<const Derived&>( *this );
    const auto& table = this->table.get();    
    const auto start = table.data.JXS( derived.startOfStoppingPower() );
    const auto length =
      this->numEnergies() * this->numDensities() * this->numTemperatures();
    return
      table.data.XSS( start, length )
      | ranges::view::chunk( this->numEnergies() );
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
	| ranges::view::transform([](auto&& e){ return std::exp(e); })
	| ranges::view::transform([](auto&& e){ return e * mev;} );
    }
    auto logValues() const {return this->logValues_;}
    auto values() const {
      return this->logValues() 
	| ranges::view::transform([](auto&& v){ return std::exp(v); })
	| ranges::view::transform([](auto&& v){ return v * (cm*cm*mev); });
    }      
  };
        
  auto makeStoppingPower = [=](auto&& tup, auto&& rangeLogValues){
    auto logTemperature = std::get<0>(tup);
    auto logDensity = std::get<1>(tup);
    return StoppingPower{logTemperature, logDensity, this->logEnergies(), rangeLogValues};
  };

  auto densAndTemps = ranges::view::cartesian_product(this->logTemperatures(),
						      this->logDensities());

  auto stoppingPowerRange = ranges::view::zip_with(makeStoppingPower,
						   densAndTemps,
						   logStoppingPowerRanges);
  
  return this->makeS0( this->numDensities(),
		       this->numTemperatures(),
		       std::move(stoppingPowerRange) );
}
