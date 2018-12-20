template<typename Derived>
class CRTP{
  std::reference_wrapper<const Table> table;

public:
  CRTP( const Table& table ) : table(table) {}

  auto logEnergies() const {
    const auto length = this->table.get().data.NXS( 4 );
    const auto start = this->table.get().data.JXS( 2 );
    std::cout << start << " " << length << "\n";
    return this->table.get().data.XSS( start, length );    
  }

  auto energies() const {
    return this->logEnergies()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }

  auto logDensities() const {
    const auto length = this->table.get().data.NXS( 5 );
    auto start = this->table.get().data.JXS( 2 )
      + this->table.get().data.NXS( 4 ) + length;
    return this->table.get().data.XSS( start, length );    
  }

  auto densities() const {
    return this->logDensities()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }

  auto logTemperatures() const {
    const auto length = this->table.get().data.NXS( 6 );
    auto start = this->table.get().data.JXS( 2 )
      + this->table.get().data.NXS( 4 )
      + this->table.get().data.NXS( 5 ) + length;
    return this->table.get().data.XSS( start, length );    
    
  }

  auto temperatures() const {
    return this->logTemperatures()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }    

  auto logStoppingPowers() const {
    const auto length = this->table.get().data.NXS( 4 ) *
      this->table.get().data.NXS( 5 ) * this->table.get().data.NXS( 6 );
    const auto index_to_start =
      static_cast<const Derived&>(*this).startOfStoppingPower();
    const auto start = this->table.get().data.JXS( index_to_start );
    return this->table.get().data.XSS( start, length );          
  }

  auto stoppingPowers() const {
    return this->logStoppingPowers()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * barn; } );
  }

};
