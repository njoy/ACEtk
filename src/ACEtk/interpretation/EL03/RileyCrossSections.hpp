class RileyCrossSections {
  const Table& table;

  auto data() const {
    const auto length = 126;
    const auto start  = this->table.data.JXS( 4 );
    return this->table.data.XSS( start, length );
  }
  
public:
  RileyCrossSections( const Table& table ) : table(table) {}

  auto energyGrid() const {
    const auto length = 126;
    const auto start  = this->table.data.JXS( 4 );
    return
      this->table.data.XSS( start, length )
      | ranges::view::stride( 14 )
      | ranges::view::reverse
      | ranges::view::transform ( [] ( auto && entry )
				  { return entry * mega(electronVolt); } );
  }

  auto values() const {
    return  this->data() | ranges::view::reverse
      | ranges::view::chunk(14)
      | ranges::view::transform( ranges::view::reverse )
      | ranges::view::transform( ranges::view::drop_exactly(1) );
  }

};
