template<typename Derived>
struct CRTP{
  std::reference_wrapper<const Table> table;

protected:
  auto get( int N ) const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 ) + N*length;
    return this->table.get().data.XSS( start, length );
  }
  
public:
  
  CRTP( const Table& table ) : table(table) {}

  auto logEnergies() const {
    return this->get( 0 );
  }

  auto energies() const {
    return this->logEnergies()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }  

  auto logStoppingPowers() const {
    return this->get( static_cast<const Derived&>(*this).stoppingPowerOffset() );
  }

  auto stoppingPowers() const {
    return this->logCrossSection()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * barn; } );
  }

};
