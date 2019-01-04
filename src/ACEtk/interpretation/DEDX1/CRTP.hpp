template<typename Derived>
class CRTP{
  std::reference_wrapper<const Table> table;

  static constexpr auto cm = dimwits::centi(dimwits::meter);
  static constexpr auto cc = cm*cm*cm;  
  static constexpr auto mev = dimwits::mega(dimwits::electronVolt);
  using DenT = decltype(1.0/cc);
  using TempT = decltype(1.0*mev);

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

  auto energies() const {
    return this->logEnergies()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }

  auto logDensities() const {
    const auto length = this->numDensities();
    const auto start = this->gridStart() + this->numEnergies();
    return this->table.get().data.XSS( start, length );    
  }

  auto densities() const {    
    return this->logDensities()
      | ranges::view::transform( [cc=this->cc]( auto&& entry ){
	  return std::exp(entry)/cc; } );
  }

  auto logTemperatures() const {
    const auto length = this->numTemperatures();
    const auto start = this->gridStart() + this->numEnergies() + this->numDensities();
    return this->table.get().data.XSS( start, length );    
  }

  auto temperatures() const {
    return this->logTemperatures()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }    

  auto logStoppingPowers() const {
    const auto length =
      this->numEnergies() * this->numDensities() * this->numTemperatures();
    const auto index_to_start =
      static_cast<const Derived&>(*this).startOfStoppingPower();
    const auto start = this->table.get().data.JXS( index_to_start );
    return this->table.get().data.XSS( start, length );
  }

  auto stoppingPowers() const {
    return this->logStoppingPowers()
      | ranges::view::transform( [cm=this->cm, mev=this->mev]( auto&& entry ) {
	  return std::exp(entry) * cm * cm * mev; } );
  }  

protected:

  template<typename Range, typename T>
  auto lowerBoundIndex(const Range& range, const T value) const noexcept(false) {
    auto first = ranges::front(range);
    auto last = ranges::back(range);
    
    if ( value < first ) {
      throw std::domain_error("Queried value is below lowest value in table");
    }
    if ( value > last ) {
      throw std::domain_error("Queried value is above upper value in table");
    }
    
    const auto rightEdge = ranges::lower_bound(range, value);
    const auto distance = ranges::distance(range.begin(), rightEdge);
    const auto index = distance - (*rightEdge != value);
    return index;
  }

  template<typename Range>  
  auto get(Range&& range, const DenT density, const TempT temperature) const {
    auto i = this->lowerBoundIndex(this->densities(), density);
    auto j = this->lowerBoundIndex(this->temperatures(), temperature);
    return ( range | ranges::view::chunk( this->numEnergies() )
	     | ranges::view::chunk( this->numDensities() ) )[i][j];
  }

public:
  auto logStoppingPowers(const DenT density, const TempT temperature) const {
    return this->get( this->logStoppingPowers(), density, temperature );
  }

  auto stoppingPowers(const DenT density, const TempT temperature) const {
    return this->get( this->logStoppingPowers(), density, temperature )
      | ranges::view::transform( [cm=this->cm, mev=this->mev]( auto&& entry ){
	  return std::exp(entry) * cm * cm * mev; } );
  }

};
