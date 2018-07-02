class RileyCrossSections {
  const Table& table;

  auto data() const {
    const auto length = 134;
    const auto start  = this->table.data.JXS( 4 ) + length;
    return this->table.data.XSS( start, length );
  }
  
public:
  RileyCrossSections( const Table& table ) : table(table) {}

  auto energyGrid() const {
    const auto length = 134;
    const auto start  = this->table.data.JXS( 4 );
    return
      this->table.data.XSS( start, length )
      | ranges::view::stride( 15 )
      | ranges::view::reverse
      | ranges::view::transform ( [] ( auto && entry )
				  { return entry * mega(electronVolt); } );
  }
  /*
  auto values() {
    return      this->data();
  }
  */
};
