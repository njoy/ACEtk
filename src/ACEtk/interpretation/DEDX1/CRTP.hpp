template<typename Derived>
class CRTP{
  std::reference_wrapper<const Table> table;

  static constexpr auto cm = dimwits::centi(dimwits::meter);
  static constexpr auto cc = cm*cm*cm;  
  static constexpr auto mev = dimwits::mega(dimwits::electronVolt);
  using DenT = decltype(1.0/cc);
  using TempT = decltype(1.0*mev);

  #include "ACEtk/interpretation/DEDX1/S0.hpp"   

protected:
  auto numEnergies() const {return this->table.get().data.NXS( 4 );}
  auto numDensities() const {return this->table.get().data.NXS( 5 );}
  auto numTemperatures() const {return this->table.get().data.NXS( 6 );}
  auto gridStart() const {return this->table.get().data.JXS( 2 );}    

public:
  CRTP( const Table& table ) : table(table) {}

  auto logEnergies() const {
    const auto length = this->numEnergies();
    const auto start = this->gridStart();
    return this->table.get().data.XSS( start, length );    
  }

  auto logDensities() const {
    const auto length = this->numDensities();
    const auto start = this->gridStart() + this->numEnergies();
    return this->table.get().data.XSS( start, length );    
  }

  auto logTemperatures() const {
    const auto length = this->numTemperatures();
    const auto start = this->gridStart() + this->numEnergies() + this->numDensities();
    return this->table.get().data.XSS( start, length );    
  }
  
  auto stoppingPowers() const {    
    auto logStoppingPowerRanges = [self = this]{
      const auto length =
        self->numEnergies() * self->numDensities() * self->numTemperatures();
      const auto index_to_start =
        static_cast<const Derived&>(*self).startOfStoppingPower();
      const auto start = self->table.get().data.JXS( index_to_start );

      return self->table.get().data.XSS( start, length )
             | ranges::view::chunk(self->numEnergies());
    }();

    using LogEnergies = decltype(this->logEnergies());    
    using LogValues = std::decay_t<decltype(logStoppingPowerRanges.front())>;

    struct StoppingPower {
      double logTemperature_;
      double logDensity_;
      LogEnergies logEnergies_;
      LogValues logValues_;
      auto logTemperature() const {return this->logTemperature_;}
      auto logDensity() const {return this->logDensity_;}
      auto logEnergies() const {return this->logEnergies_;}
      auto logValues() const {return this->logValues_;}      
    };
        
    auto makeStoppingPower = [=](auto&& tup, auto&& rangeLogValues){
      auto logTemperature = ranges::get<0>(tup);
      auto logDensity = ranges::get<1>(tup);
      return StoppingPower{logTemperature, logDensity, this->logEnergies(), rangeLogValues};
    };

    auto densAndTemps = ranges::view::cartesian_product(this->logTemperatures(),
							this->logDensities());

    auto stoppingPowerRange = ranges::view::zip_with(makeStoppingPower,
						     densAndTemps,
						     logStoppingPowerRanges);

    return this->makeS0(this->numDensities(), std::move(stoppingPowerRange));

  }

};

/*

  auto energies() const {
    return this->logEnergies()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }
  
  auto densities() const {    
    return this->logDensities()
      | ranges::view::transform( [cc=this->cc]( auto&& entry ){
	  return std::exp(entry)/cc; } );
  }
  
  auto temperatures() const {
    return this->logTemperatures()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }    
*/
