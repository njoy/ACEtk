class MottScatteringCorrection {
  const Table& table;

  auto angle() const {
    const auto length = this->table.data.NXS( 4 );
    const auto start  = this->table.data.JXS(3) + 5*length;
    return this->table.data.XSS( start, length ) | ranges::view::reverse;
  }
  
public:
  MottScatteringCorrection( const Table& table ) : table(table) {}

  auto energyGrid() const {
    const auto length = this->table.data.NXS( 4 );
    const auto start  = this->table.data.JXS( 3 );
    return
      this->table.data.XSS( start, length )
      | ranges::view::reverse
      | ranges::view::transform ( [] ( auto && entry )
				  { return entry * mega(electronVolt); } );
  }

  auto values() {
    return      this->angle();
  }
  
};
