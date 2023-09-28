class RileyCrossSection {
  const Table& table;
  static constexpr int length = 126;

  static constexpr int params_per_energy() { return 14; }

public:
  RileyCrossSection( const Table& table ) : table(table) {}

  auto energyGrid() const {
    const auto start  = this->table.data().JXS( 4 );
    return
      this->table.data().XSS( start, RileyCrossSection::length )
      | ranges::views::stride( params_per_energy() )
      | ranges::cpp20::views::reverse
      | ranges::cpp20::views::transform ( [] ( auto && entry )
				  { return entry * kilo(electronVolt); } );
  }

  auto values() const {
    const auto start = this->table.data().JXS( 4 );
    return
      this->table.data().XSS( start, RileyCrossSection::length )
      | ranges::cpp20::views::reverse
      | ranges::views::chunk( params_per_energy() )
      | ranges::cpp20::views::transform( ranges::cpp20::views::reverse )
      | ranges::cpp20::views::transform( ranges::views::drop_exactly(1) );
  }

};
