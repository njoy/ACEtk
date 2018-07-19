class RileyCrossSection {
  const Table& table;
  static constexpr int length = 126;

  static constexpr int params_per_energy() { return 14; }
  
public:
  RileyCrossSection( const Table& table ) : table(table) {}

  auto energyGrid() const {
    const auto start  = this->table.data.JXS( 4 );
    return
      this->table.data.XSS( start, RileyCrossSection::length )
      | ranges::view::stride( params_per_energy() )
      | ranges::view::reverse
      | ranges::view::transform ( [] ( auto && entry )
				  { return entry * kilo(electronVolt); } );
  }

  auto values() const {
    const auto start = this->table.data.JXS( 4 );
    return
      this->table.data.XSS( start, RileyCrossSection::length )
      | ranges::view::reverse
      | ranges::view::chunk( params_per_energy() )
      | ranges::view::transform( ranges::view::reverse )
      | ranges::view::transform( ranges::view::drop_exactly(1) );
  }

};
